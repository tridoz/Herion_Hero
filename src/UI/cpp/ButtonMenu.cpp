//
// Created by tridoz on 20/05/26.
//

#include "../hpp/ButtonMenu.hpp"

#include "AST.hpp"
#include "HerionFileException.hpp"
#include "JSONParser.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keyboard.h"
#include "SliderSelector.hpp"

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

auto ButtonMenu::LoadConfiguration(const std::string& filename) -> void {
    std::ifstream file;
    try {
        FileOpener::OpenFileInput(file, filename);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw ex;
    }

    try {
        this->scale = JSONParser::graphics::GetScale();
    } catch (HerionException::File::FileMalformedException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw ex;
    }

    std::stringstream ss;
    ss << file.rdbuf();

    CMLDocument document = (new Parser((new Lexer(ss.str()))->Tokenize()))->Parse();

    buttons.clear();
    texts.clear();
    slider_selectors.clear();

    // std::cout << document.components[0].ToString() << '\n';

    this->background = texture_manager->GetTextureByName(
        GetParameter<CMLString>("background_path", document.components[0].parameters).value
    );

    this->char_dim = GetParameter<CMLNumber>("char_dim", document.components[0].parameters).value;
    for (const CMLComponent& component : document.components[0].children) {
        this->BuildRow(component, document.components[0].parameters);
    }
}

auto ButtonMenu::BuildRow(CMLComponent cmp, std::vector<CMLParameter> params) -> void {
    for (const CMLComponent& component : cmp.children) {
        std::vector<CMLParameter> p;
        p.reserve(params.size() + cmp.parameters.size());

        p.insert(p.end(), cmp.parameters.begin(), cmp.parameters.end());
        p.insert(p.end(), params.begin(), params.end());
        this->BuildComponent(component, p);
    }
}

auto ButtonMenu::BuildComponent(CMLComponent cmp, std::vector<CMLParameter> params) -> void {
    std::vector<Renderable*> renderables_unselected;
    std::vector<Renderable*> renderables_selected;
    std::vector<Renderable*> renderables_clicked;
    params.insert(params.end(), cmp.parameters.begin(), cmp.parameters.end());

    // std::cout << cmp.name << '\n';
    // for (const CMLParameter& p : params) {
    //     std::cout << p.ToString() << '\n';
    // }

    // std::cout << "\n\n\n";
    float cumulative_x = GetParameter<CMLNumber>("starting_x", params).value;

    if (cmp.name == "Button") {
        std::string text = GetParameter<CMLString>("text", std::move(params)).value;
        int characters = 0;
        for (char c : text) {
            Texture* char_tex_unselected = nullptr;
            Texture* char_tex_selected = nullptr;
            Texture* char_tex_clicked = nullptr;

            try {
                if (std::isupper(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/UppercaseLetters/" +
                        std::string(1, c) + ".png"
                    );

                    char_tex_selected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                        "/UppercaseLetters/Selected/" + std::string(1, c) + ".png"
                    );
                } else if (std::islower(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/LowercaseLetters/" +
                        std::string(1, c) + ".png"
                    );
                    // char_tex_selected = texture_manager->GetTextureByName(
                    //     "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                    //     "/LowercaseLetters/Selected" + std::string(1, c)
                    //     +
                    //     ".png"
                    // );
                } else if (std::isdigit(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/Numbers/" +
                        std::string(1, c) + ".png"
                    );
                    // char_tex_selected = texture_manager->GetTextureByName(
                    //     "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/Numbers/Selected/" +
                    //     std::string(1, c) + ".png"
                    // );
                } else if (isspecial(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/SpecialCharacters/" +
                        GetNameOfSpecialChar(c) + ".png"
                    );
                    char_tex_selected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                        "/SpecialCharacters/Selected" + GetNameOfSpecialChar(c) + ".png"
                    );
                } else if (isspace(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                        "/SpecialCharacters/space.png"
                    );
                    char_tex_selected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                        "/SpecialCharacters/space.png"
                    );
                }
            } catch (HerionException::File::FileNotFoundException& ex) {
                ex.UpdateStackTrace(GET_CONTEXT());
                throw;
            }

            SDL_FRect char_rect{
                .x = cumulative_x,
                .y = GetParameter<CMLNumber>("starting_y", params).value,
                .w = char_dim * scale,
                .h = char_dim * scale
            };

            cumulative_x += char_dim * scale + 5;
            renderables_unselected.emplace_back(new Renderable(char_tex_unselected, new SDL_FRect{char_rect}));
            renderables_selected.emplace_back(new Renderable(char_tex_selected, new SDL_FRect{char_rect}));
        }

        Button* btn = new Button();
        btn->addRenderables(Button::State::UNACTIVE, renderables_unselected);
        btn->addRenderables(Button::State::FOCUSED, renderables_selected);

        if (GetParameter<CMLString>("function", params).value == "RETURN_VALUE") {
            btn->SetText(text);
            btn->SetOnClickReturn([btn] { return btn->GetText(); });
        } else {
            btn->SetOnClick(buttons_functions.at(GetParameter<CMLString>("function", params).value));
        }

        SDL_FRect interaction_rect = {
            .x = renderables_unselected.front()->GetRect()->x,
            .y = renderables_unselected.front()->GetRect()->y,
            .w = (renderables_unselected.back()->GetRect()->x + renderables_unselected.back()->GetRect()->w) -
                 renderables_unselected.front()->GetRect()->x,
            .h = renderables_unselected.front()->GetRect()->h
        };

        btn->SetInteractionRect(interaction_rect);

        buttons.emplace(GetParameter<CMLString>("id", params).value, btn);

    } else if (cmp.name == "StaticText") {
        std::string text = GetParameter<CMLString>("text", params).value;
        int characters = 0;
        for (char c : text) {
            Texture* char_tex_unselected = nullptr;
            Texture* char_tex_selected = nullptr;
            Texture* char_tex_clicked = nullptr;

            try {
                if (std::isupper(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/UppercaseLetters/" +
                        std::string(1, c) + ".png"
                    );

                    char_tex_selected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                        "/UppercaseLetters/Selected/" + std::string(1, c) + ".png"
                    );
                } else if (std::islower(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/LowercaseLetters/" +
                        std::string(1, c) + ".png"
                    );
                    // char_tex_selected = texture_manager->GetTextureByName(
                    //     "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                    //     "/LowercaseLetters/Selected" + std::string(1, c)
                    //     +
                    //     ".png"
                    // );
                } else if (std::isdigit(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/Numbers/" +
                        std::string(1, c) + ".png"
                    );
                    // char_tex_selected = texture_manager->GetTextureByName(
                    //     "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/Numbers/Selected/" +
                    //     std::string(1, c) + ".png"
                    // );
                } else if (isspecial(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/SpecialCharacters/" +
                        GetNameOfSpecialChar(c) + ".png"
                    );
                    char_tex_selected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                        "/SpecialCharacters/Selected" + GetNameOfSpecialChar(c) + ".png"
                    );
                } else if (isspace(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                        "/SpecialCharacters/space.png"
                    );
                    char_tex_selected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                        "/SpecialCharacters/space.png"
                    );
                }
            } catch (HerionException::File::FileNotFoundException& ex) {
                ex.UpdateStackTrace(GET_CONTEXT());
                throw;
            }

            SDL_FRect char_rect{
                .x = cumulative_x,
                .y = GetParameter<CMLNumber>("starting_y", params).value,
                .w = char_dim * scale,
                .h = char_dim * scale
            };

            cumulative_x += char_dim * scale + 5;
            renderables_unselected.emplace_back(new Renderable((char_tex_unselected), new SDL_FRect{char_rect}));
        }

        Text* txt = new Text();
        txt->SetRenderables(renderables_unselected);
        texts.emplace(GetParameter<CMLString>("id", params).value, txt);

    } else if (cmp.name == "DynamicText") {
        std::string text = GetText(GetParameter<CMLString>("reference", params).value);
        int characters = 0;
        for (char c : text) {
            Texture* char_tex_unselected = nullptr;
            Texture* char_tex_selected = nullptr;
            Texture* char_tex_clicked = nullptr;

            try {
                if (std::isupper(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/UppercaseLetters/" +
                        std::string(1, c) + ".png"
                    );

                    char_tex_selected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                        "/UppercaseLetters/Selected/" + std::string(1, c) + ".png"
                    );
                } else if (std::islower(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/LowercaseLetters/" +
                        std::string(1, c) + ".png"
                    );
                    // char_tex_selected = texture_manager->GetTextureByName(
                    //     "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                    //     "/LowercaseLetters/Selected" + std::string(1, c)
                    //     +
                    //     ".png"
                    // );
                } else if (std::isdigit(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/Numbers/" +
                        std::string(1, c) + ".png"
                    );
                    // char_tex_selected = texture_manager->GetTextureByName(
                    //     "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/Numbers/Selected/" +
                    //     std::string(1, c) + ".png"
                    // );
                } else if (isspecial(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value + "/SpecialCharacters/" +
                        GetNameOfSpecialChar(c) + ".png"
                    );
                    char_tex_selected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                        "/SpecialCharacters/Selected" + GetNameOfSpecialChar(c) + ".png"
                    );
                } else if (isspace(c)) {
                    char_tex_unselected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                        "/SpecialCharacters/space.png"
                    );
                    char_tex_selected = texture_manager->GetTextureByName(
                        "Assets/Font/" + GetParameter<CMLString>("font_style", params).value +
                        "/SpecialCharacters/space.png"
                    );
                }
            } catch (HerionException::File::FileNotFoundException& ex) {
                ex.UpdateStackTrace(GET_CONTEXT());
                throw;
            }

            SDL_FRect char_rect{
                .x = cumulative_x,
                .y = GetParameter<CMLNumber>("starting_y", params).value,
                .w = char_dim * scale,
                .h = char_dim * scale
            };

            cumulative_x += char_dim * scale + 5;
            renderables_unselected.emplace_back(new Renderable((char_tex_unselected), new SDL_FRect{char_rect}));
        }

        Text* txt = new Text();
        txt->SetRenderables(renderables_unselected);
        texts.emplace(GetParameter<CMLString>("id", params).value, txt);
    } else if (cmp.name == "SliderSelector") {
        SliderSelector* slider = new SliderSelector();
        Texture* slider_bar_txt = texture_manager->GetTextureByName("Assets/Ui/Bars/SliderBar.png");
        SDL_FRect slider_bar_rect = {
            .x = cumulative_x,
            .y = GetParameter<CMLNumber>("starting_y", params).value,
            .w = GetParameter<CMLNumber>("length", params).value * scale,
            .h = char_dim * scale
        };

        slider->SetSliderBarRect(slider_bar_rect);
        slider->SetSliderBarTexture(slider_bar_txt);

        Texture* slider_button_txt = texture_manager->GetTextureByName("Assets/Ui/Buttons/Game/SliderButton.png");
        const std::string value_to_set = GetParameter<CMLString>("value_to_set", params).value;
        float volume_percentage = 0;

        if (value_to_set == "MASTER_VOLUME")
            volume_percentage = JSONParser::audio::GetMasterVolume();
        else if (value_to_set == "MUSIC_VOLUME")
            volume_percentage = JSONParser::audio::GetMusicVolume();
        else if (value_to_set == "SFX_VOLUME")
            volume_percentage = JSONParser::audio::GetSFXVolume();

        const float bar_percentage = GetParameter<CMLNumber>("length", params).value / 100 * volume_percentage * scale;
        const SDL_FRect slider_button_rect = {
            .x = slider_bar_rect.x - (char_dim * scale / 2.0f) + bar_percentage,
            .y = slider_bar_rect.y + (slider_bar_rect.h / 2.0f) - (char_dim * scale / 2.0f),
            .w = char_dim * scale,
            .h = char_dim * scale
        };

        slider->SetLength(GetParameter<CMLNumber>("length", params).value);
        slider->SetMaxMinStep(
            GetParameter<CMLNumber>("max_value", params).value,
            GetParameter<CMLNumber>("min_value", params).value,
            GetParameter<CMLNumber>("step", params).value
        );

        slider->SetSliderButtonRect(slider_button_rect);
        slider->SetSliderButtonTexture(slider_button_txt);

        slider_selectors.emplace(GetParameter<CMLString>("id", params).value, slider);

        if (GetParameter<CMLString>("action", params).value == "SETTER") {
            if (GetParameter<CMLString>("value_to_set", params).value == "MASTER_VOLUME")
                slider->SetToSet("MASTER_VOLUME");
            if (GetParameter<CMLString>("value_to_set", params).value == "MUSIC_VOLUME")
                slider->SetToSet("MUSIC_VOLUME");
            if (GetParameter<CMLString>("value_to_set", params).value == "SFX_VOLUME")
                slider->SetToSet("SFX_VOLUME");
        }
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
