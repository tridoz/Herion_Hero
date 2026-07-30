//
// Created by tridoz on 20/05/26.
//

#include "../hpp/ButtonMenu.hpp"
#include "JSONParser.hpp"
#include "SDL3/SDL_events.h"

ButtonMenu::~ButtonMenu() {
}

bool ButtonMenu::CheckCollision(std::vector<SDL_FRect> buttons, float x, float y) {
    for (SDL_FRect button : buttons) {
        if (x >= button.x && x <= button.x + button.w && y >= button.y && y <= button.y + button.h) {
            return true;
        }
    }
    return false;
}

Button* ButtonMenu::GetCollisionButton(float x, float y) {
    for (const auto& [id, btn] : this->buttons) {
        if (CheckCollision(btn->GetRects(), x, y)) {
            return btn;
        }
    }

    return nullptr;
}

SliderSelector* ButtonMenu::GetSliderSelector(float x, float y) {

    for (const auto& [name, slider] : slider_selectors) {

        SDL_FRect* rect = slider->GetSliderButtonRect(x, y);
        if (rect == nullptr)
            continue;

        return slider;
    }

    return nullptr;
}

void ButtonMenu::LoadConfiguration(const std::string& cfg_json_filepath) {
    this->filepath = cfg_json_filepath;

    try {
        JSONParser::menu_configuration::SetConfigFile(cfg_json_filepath);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    try {
        this->scale = JSONParser::graphics::GetScale();
        this->type = JSONParser::menu_configuration::GetMenuType();
        this->background_filepath = JSONParser::menu_configuration::GetBackgroundImagePath();
        this->button_style = JSONParser::menu_configuration::GetButtonStyle();
        this->font_style = JSONParser::menu_configuration::GetFontStyle();
        this->start_y = JSONParser::menu_configuration::GetStartY();
        this->button_y_offset = JSONParser::menu_configuration::GetButtonYOffset();
        this->center_piece_offset = JSONParser::menu_configuration::GetCenterPieceOffset() * scale;
        this->char_width = JSONParser::menu_configuration::GetCharWidth();
    } catch (HerionException::File::FileMalformedException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    try {
        this->background = texture_manager->GetTextureByName(this->background_filepath);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    const int num_rows = JSONParser::menu_configuration::GetNumRows();
    float current_y = start_y;

    buttons.clear();
    texts.clear();
    slider_selectors.clear();

    for (int row_number = 0; row_number < num_rows; row_number++) {
        const int starting_x = JSONParser::menu_configuration::GetRowStartingX(row_number) * scale;
        const int button_x_offset = JSONParser::menu_configuration::GetRowButtonXOffset(row_number);
        const int num_elements = JSONParser::menu_configuration::GetRowNumElements(row_number);

        float cumulative_x = static_cast<float>(starting_x);
        float row_height = 0.0f;

        for (int element_number = 0; element_number < num_elements; element_number++) {
            const JSONParser::menu_configuration::RowElementFields menu_element_characteristic =
                JSONParser::menu_configuration::GetRowElementFields(row_number, element_number);

            std::string text;

            std::vector<Renderable*> renderables;

            Texture* left_texture = nullptr;
            Texture* center_texture = nullptr;
            Texture* right_texture = nullptr;

            try {
                left_texture =
                    texture_manager->GetTextureByName("Assets/Ui/Buttons/" + this->button_style + "/ButtonLeft.png");
                center_texture =
                    texture_manager->GetTextureByName("Assets/Ui/Buttons/" + this->button_style + "/ButtonCenter.png");
                right_texture =
                    texture_manager->GetTextureByName("Assets/Ui/Buttons/" + this->button_style + "/ButtonRight.png");
            } catch (HerionException::File::FileNotFoundException& ex) {
                ex.UpdateStackTrace(GET_CONTEXT());
                throw;
            }

            float left_w, left_h, center_w, center_h, right_w, right_h;

            SDL_GetTextureSize(left_texture->GetTexture(), &left_w, &left_h);
            SDL_GetTextureSize(center_texture->GetTexture(), &center_w, &center_h);
            SDL_GetTextureSize(right_texture->GetTexture(), &right_w, &right_h);

            SDL_FRect left_rect = {.x = cumulative_x, .y = current_y, .w = left_w * scale, .h = left_h * scale};

            renderables.emplace_back(new Renderable(left_texture, new SDL_FRect{left_rect}));

            float char_w = this->char_width * this->scale;

            float text_total_w = 0;

            if (menu_element_characteristic.text.has_value()) {
                text = (menu_element_characteristic.type == "DYNAMIC_TEXT")
                           ? GetText(menu_element_characteristic.text.value())
                           : menu_element_characteristic.text.value();
                text_total_w = text.size() * char_w;
            } else {
                text_total_w = menu_element_characteristic.length.value();
            }

            SDL_FRect center_rect = {
                .x = cumulative_x + left_rect.w,
                .y = current_y + center_piece_offset,
                .w = text_total_w,
                .h = center_h * scale
            };

            renderables.emplace_back(new Renderable(center_texture, new SDL_FRect{center_rect}));

            SDL_FRect right_rect = {
                .x = center_rect.x + center_rect.w, .y = current_y, .w = right_w * scale, .h = right_h * scale
            };

            renderables.emplace_back(new Renderable(right_texture, new SDL_FRect{right_rect}));

            float char_x = center_rect.x;

            if (menu_element_characteristic.type != "SLIDER_SELECTOR") {
                for (char c : text) {
                    Texture* char_tex = nullptr;

                    try {
                        if (std::isupper(c))
                            char_tex = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/UppercaseLetters/" + std::string(1, c) + ".png"
                            );
                        else if (std::islower(c))
                            char_tex = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/LowercaseLetters/" + std::string(1, c) + ".png"
                            );
                        else if (std::isdigit(c))
                            char_tex = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/Numbers/" + std::string(1, c) + ".png"
                            );
                        else if (isspecial(c))
                            char_tex = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/SpecialCharacters/" + GetNameOfSpecialChar(c) +
                                ".png"
                            );
                        else if (isspace(c))
                            char_tex = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/SpecialCharacters/space.png"
                            );
                    } catch (HerionException::File::FileNotFoundException& ex) {
                        ex.UpdateStackTrace(GET_CONTEXT());
                        throw;
                    }

                    float cw, ch;

                    SDL_GetTextureSize(char_tex->GetTexture(), &cw, &ch);
                    SDL_FRect char_rect = {
                        .x = char_x + (char_w - cw * scale) / 2.0f,
                        .y = center_rect.y + (center_rect.h - ch * scale) / 2.0f,
                        .w = cw * scale,
                        .h = ch * scale
                    };
                    renderables.emplace_back(new Renderable(char_tex, new SDL_FRect{char_rect}));

                    char_x += char_w;
                }

                row_height = std::max({row_height, left_rect.h, center_rect.h, right_rect.h});

                if (menu_element_characteristic.type == "BUTTON") {
                    Button* btn = new Button();
                    btn->SetRenderables(renderables);

                    if (menu_element_characteristic.action.value() == "RETURN_VALUE") {
                        btn->SetText(menu_element_characteristic.return_value.value());
                        btn->SetOnClickReturn([btn] { return btn->GetText(); });
                    } else {
                        if (!buttons_functions.contains(menu_element_characteristic.action.value())) {
                            THROW_FILE_NOT_FOUND(menu_element_characteristic.action.value());
                        }

                        btn->SetOnClick(buttons_functions.at(menu_element_characteristic.action.value()));
                    }

                    buttons.emplace(menu_element_characteristic.id, btn);
                } else if (menu_element_characteristic.type.contains("TEXT")) {
                    Text* txt = new Text();
                    txt->SetRenderables(renderables);
                    texts.emplace(menu_element_characteristic.id, txt);
                }

            } else {
                SliderSelector* slider = new SliderSelector();

                Texture* slider_bar_txt = texture_manager->GetTextureByName("Assets/Ui/Bars/SliderBar.png");

                float srw, srh;
                SDL_GetTextureSize(slider_bar_txt->GetTexture(), &srw, &srh);
                SDL_FRect slider_bar_rect = {
                    center_rect.x,
                    center_rect.y + (menu_element_characteristic.slider_bar_offset.value() * scale),
                    text_total_w,
                    srh * scale
                };

                slider->SetSliderBarRect(slider_bar_rect);
                slider->SetSliderBarTexture(slider_bar_txt);

                Texture* slider_button_txt =
                    texture_manager->GetTextureByName("Assets/Ui/Buttons/Game/SliderButton.png");

                SDL_GetTextureSize(slider_button_txt->GetTexture(), &srw, &srh);
                const std::string value_to_set = menu_element_characteristic.value_to_set.value();
                float volume_percentage = 0;
                if (value_to_set == "MASTER_VOLUME")
                    volume_percentage = JSONParser::audio::GetMasterVolume();
                else if (value_to_set == "MUSIC_VOLUME")
                    volume_percentage = JSONParser::audio::GetMusicVolume();
                else if (value_to_set == "SFX_VOLUME")
                    volume_percentage = JSONParser::audio::GetSFXVolume();

                const float bar_percentage = text_total_w / 100 * volume_percentage;

                const float x = center_rect.x + bar_percentage;

                const SDL_FRect slider_button_rect = {
                    x - (left_rect.w * scale / 2),
                    slider_bar_rect.y + (slider_bar_rect.h / 2.0f) - (center_rect.h * scale / 2.0f),
                    left_rect.w * scale,
                    center_rect.h * scale
                };

                slider->SetRenderable(renderables);

                slider->SetLength(menu_element_characteristic.length.value());
                slider->SetMaxMinStep(
                    menu_element_characteristic.max_value.value(),
                    menu_element_characteristic.min_value.value(),
                    menu_element_characteristic.step.value()
                );
                slider->SetSliderButtonRect(slider_button_rect);
                slider->SetSliderButtonTexture(slider_button_txt);

                slider_selectors.emplace(menu_element_characteristic.id, slider);

                if (!menu_element_characteristic.action.has_value())
                    continue;

                if (menu_element_characteristic.action.value() == "SETTER")
                    if (menu_element_characteristic.value_to_set.value() == "MASTER_VOLUME")
                        slider->SetToSet("MASTER_VOLUME");
                    else if (menu_element_characteristic.value_to_set.value() == "MUSIC_VOLUME")
                        slider->SetToSet("MUSIC_VOLUME");
                    else if (menu_element_characteristic.value_to_set.value() == "SFX_VOLUME")
                        slider->SetToSet("SFX_VOLUME");
            }

            cumulative_x += left_rect.w + center_rect.w + right_rect.w + button_x_offset;
        }

        current_y += row_height + button_y_offset;
    }
}

void ButtonMenu::Draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderTexture(renderer, background->GetTexture(), nullptr, &background_rect);

    for (const auto& [id, button] : buttons) {
        button->Draw(renderer);
    }

    for (const auto& [id, text] : texts) {
        text->Draw(renderer);
    }

    for (const auto& [id, slider] : slider_selectors) {
        slider->Draw(renderer);
    }
}
