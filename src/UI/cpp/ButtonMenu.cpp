//
// Created by tridoz on 20/05/26.
//

#include "../hpp/ButtonMenu.hpp"
#include "JSONParser.hpp"
#include "SDL3/SDL_events.h"

ButtonMenu::ButtonMenu() = default;

ButtonMenu::~ButtonMenu() {
}

auto ButtonMenu::CheckCollision(const std::vector<SDL_FRect>& rects, float x, float y) -> bool {
    return true;
}

auto ButtonMenu::GetCollisionButton(float x, float y) -> Button* {
    for (const auto& [id, btn] : this->buttons) {
        const SDL_FPoint* point = new SDL_FPoint{.x = x, .y = y};
        const SDL_FRect* interaction_rect = btn->GetInteractionRect();
        if (SDL_PointInRectFloat(point, interaction_rect)) {
            return btn;
        }
    }

    return nullptr;
}

auto ButtonMenu::GetSliderSelector(float x, float y) -> SliderSelector* {

    for (const auto& [name, slider] : slider_selectors) {

        SDL_FRect* rect = slider->GetSliderButtonRect(x, y);
        if (rect == nullptr)
            continue;

        return slider;
    }

    return nullptr;
}

auto ButtonMenu::LoadConfiguration(const std::string& cfg_json_filepath) -> void {
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
        const auto starting_x = static_cast<float>(JSONParser::menu_configuration::GetRowStartingX(row_number)) * scale;
        const auto button_x_offset =
            static_cast<float>(JSONParser::menu_configuration::GetRowButtonXOffset(row_number));
        const auto num_elements = JSONParser::menu_configuration::GetRowNumElements(row_number);

        float cumulative_x = static_cast<float>(starting_x) * scale;
        float row_height = 0.0f;

        for (int element_number = 0; element_number < num_elements; element_number++) {

            const JSONParser::menu_configuration::RowElementFields menu_element_characteristic =
                JSONParser::menu_configuration::GetRowElementFields(row_number, element_number);

            std::string text;

            if (menu_element_characteristic.type == "DYNAMIC_TEXT") {
                text = this->GetText(menu_element_characteristic.text.value());
            } else if (
                menu_element_characteristic.type == "BUTTON" || menu_element_characteristic.type == "STATIC_TEXT"
            ) {
                text = menu_element_characteristic.text.value();
            }

            std::vector<Renderable*> renderables_unselected;
            std::vector<Renderable*> renderables_selected;
            std::vector<Renderable*> renderables_clicked;

            if (menu_element_characteristic.type != "SLIDER_SELECTOR") {

                int characters = 0;
                for (char c : text) {
                    Texture* char_tex_unselected = nullptr;
                    Texture* char_tex_selected = nullptr;
                    Texture* char_tex_clicked = nullptr;

                    try {
                        if (std::isupper(c)) {
                            char_tex_unselected = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/UppercaseLetters/" + std::string(1, c) + ".png"
                            );

                            char_tex_selected = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/UppercaseLetters/Selected/" + std::string(1, c) +
                                ".png"
                            );
                        } else if (std::islower(c)) {
                            char_tex_unselected = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/LowercaseLetters/" + std::string(1, c) + ".png"
                            );
                            // char_tex_selected = texture_manager->GetTextureByName(
                            //     "Assets/Font/" + this->font_style + "/LowercaseLetters/Selected" + std::string(1, c)
                            //     +
                            //     ".png"
                            // );
                        } else if (std::isdigit(c)) {
                            char_tex_unselected = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/Numbers/" + std::string(1, c) + ".png"
                            );
                            // char_tex_selected = texture_manager->GetTextureByName(
                            //     "Assets/Font/" + this->font_style + "/Numbers/Selected/" + std::string(1, c) + ".png"
                            // );
                        } else if (isspecial(c)) {
                            char_tex_unselected = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/SpecialCharacters/" + GetNameOfSpecialChar(c) +
                                ".png"
                            );
                            char_tex_selected = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/SpecialCharacters/Selected" +
                                GetNameOfSpecialChar(c) + ".png"
                            );
                        } else if (isspace(c)) {
                            char_tex_unselected = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/SpecialCharacters/space.png"
                            );
                            char_tex_selected = texture_manager->GetTextureByName(
                                "Assets/Font/" + this->font_style + "/SpecialCharacters/space.png"
                            );
                        }
                    } catch (HerionException::File::FileNotFoundException& ex) {
                        ex.UpdateStackTrace(GET_CONTEXT());
                        throw;
                    }

                    SDL_FRect char_rect = {
                        .x = cumulative_x,
                        .y = start_y + ((char_width * scale + button_y_offset) * static_cast<float>(row_number)),
                        .w = char_width * scale,
                        .h = char_width * scale
                    };

                    cumulative_x += char_width * scale + 5;
                    renderables_unselected.emplace_back(new Renderable(char_tex_unselected, new SDL_FRect{char_rect}));
                    renderables_selected.emplace_back(new Renderable(char_tex_selected, new SDL_FRect{char_rect}));
                }

                if (menu_element_characteristic.type == "BUTTON") {
                    Button* btn = new Button();
                    btn->addRenderables(Button::State::UNACTIVE, renderables_unselected);
                    btn->addRenderables(Button::State::FOCUSED, renderables_selected);

                    if (menu_element_characteristic.action.value() == "RETURN_VALUE") {
                        btn->SetText(menu_element_characteristic.return_value.value());
                        btn->SetOnClickReturn([btn] { return btn->GetText(); });
                    } else {
                        if (!buttons_functions.contains(menu_element_characteristic.action.value())) {
                            THROW_FILE_NOT_FOUND(menu_element_characteristic.action.value());
                        }

                        btn->SetOnClick(buttons_functions.at(menu_element_characteristic.action.value()));
                    }

                    SDL_FRect interaction_rect = {
                        .x = renderables_unselected.front()->GetRect()->x,
                        .y = renderables_unselected.front()->GetRect()->y,
                        .w = (renderables_unselected.back()->GetRect()->x +
                              renderables_unselected.back()->GetRect()->w) -
                             renderables_unselected.front()->GetRect()->x,
                        .h = renderables_unselected.front()->GetRect()->h
                    };

                    btn->SetInteractionRect(interaction_rect);

                    buttons.emplace(menu_element_characteristic.id, btn);
                } else if (menu_element_characteristic.type.contains("TEXT")) {
                    Text* txt = new Text();
                    txt->SetRenderables(renderables_unselected);
                    texts.emplace(menu_element_characteristic.id, txt);
                }

            } else {
                SliderSelector* slider = new SliderSelector();

                Texture* slider_bar_txt = texture_manager->GetTextureByName("Assets/Ui/Bars/SliderBar.png");

                SDL_FRect slider_bar_rect = {
                    .x = cumulative_x,
                    .y = start_y + ((char_width * scale + button_y_offset) * static_cast<float>(row_number)),
                    .w = menu_element_characteristic.length.value() * scale,
                    .h = char_width * scale
                };

                slider->SetSliderBarRect(slider_bar_rect);
                slider->SetSliderBarTexture(slider_bar_txt);

                Texture* slider_button_txt =
                    texture_manager->GetTextureByName("Assets/Ui/Buttons/Game/SliderButton.png");

                const std::string value_to_set = menu_element_characteristic.value_to_set.value();
                float volume_percentage = 0;

                if (value_to_set == "MASTER_VOLUME")
                    volume_percentage = JSONParser::audio::GetMasterVolume();
                else if (value_to_set == "MUSIC_VOLUME")
                    volume_percentage = JSONParser::audio::GetMusicVolume();
                else if (value_to_set == "SFX_VOLUME")
                    volume_percentage = JSONParser::audio::GetSFXVolume();

                const float bar_percentage =
                    menu_element_characteristic.length.value() / 100 * volume_percentage * scale;

                const SDL_FRect slider_button_rect = {
                    .x = slider_bar_rect.x - (char_width * scale / 2.0f) + bar_percentage,
                    .y = slider_bar_rect.y + (slider_bar_rect.h / 2.0f) - (char_width * scale / 2.0f),
                    .w = char_width * scale,
                    .h = char_width * scale
                };

                // slider->SetRenderable(renderables_unselected);

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

                cumulative_x += menu_element_characteristic.length.value() * scale;
            }
            cumulative_x += button_x_offset;
        }

        current_y += row_height + static_cast<float>(button_y_offset);
    }
}

auto ButtonMenu::Draw(SDL_Renderer* renderer) const -> void {
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
