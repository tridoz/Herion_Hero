//
// Created by trida on 11/19/25.
//

#ifndef HERION_HERO_MENU_HPP
#define HERION_HERO_MENU_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "../../Textures/hpp/TextureManager.hpp"
#include "../../Utils/hpp/ButtonsFunctions.hpp"
#include "../../Utils/hpp/CMD.hpp"
#include "../../Utils/hpp/JSONParser.hpp"
#include "../../Utils/hpp/Logger.hpp"
#include "Button.hpp"
#include "SliderSelector.hpp"
#include "Text.hpp"

class Menu {

  protected:
    TextureManager* texture_manager;
    Texture* background;

    float mouse_offset;
    const std::string base_path = "../";
    float scale;
    float char_width;
    std::string button_style;

    SDL_FRect background_rect;

    std::unordered_map<std::string, std::function<void()>> buttons_functions;

    std::unordered_map<std::string, Button*> buttons;
    std::unordered_map<std::string, Text*> texts;
    std::unordered_map<std::string, SliderSelector*> slider_selectors;

    std::string filepath;
    std::string background_filepath;
    std::string type;
    std::string font_style;

    auto Rescale(SDL_FRect*) -> void;

    auto GetText(const std::string&) -> std::string;

    auto isspecial(const char) -> bool;

    auto GetNameOfSpecialChar(const char) -> std::string;
    auto split(const std::string&) -> std::vector<std::string>;

    virtual auto CheckCollision(const std::vector<SDL_FRect>&, float, float) -> bool = 0;

  public:
    Menu();
    ~Menu();
    auto SetDimension(float, float) -> void;
    auto SetTextureManager(TextureManager*) -> void;
    auto GetButton(const std::string&) const -> Button*;
    auto GetButtons() const -> std::vector<Button*>;

    virtual auto GetCollisionButton(float, float) -> Button* = 0;
    virtual auto LoadConfiguration(const std::string&) -> void = 0;
    virtual auto Draw(SDL_Renderer*) const -> void = 0;
    auto SetMouseOffset(float) -> void;
    auto ReloadConfiguration() -> void;
};

#endif // HERION_HERO_MENU_HPP
