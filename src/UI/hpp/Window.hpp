#ifndef HERION_HERO_WINDOW_HPP
#define HERION_HERO_WINDOW_HPP

// SDL3 INCLUDES
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

// STD INCLUDES
#include <string>

// CUSTOM INCLUDES
#include <random>

#include "../../Utils/hpp/COLORS.hpp"
#include "../../Utils/hpp/JSONParser.hpp"
#include "../../Utils/hpp/Logger.hpp"
#include "Menu.hpp"
#include "SDL3/SDL_mouse.h"

class Window {

  private:
    int flags;
    int is_open;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::unordered_map<std::string, Menu*> menus;
    Menu* current_menu;

    std::unordered_map<std::string, SDL_Cursor*> Cursors;
    std::string current_cursor_name;

    int width, height;

  public:
    Window();
    Window(const std::string&);
    Window(const std::string&, int, int);

    ~Window();

    [[nodiscard]] auto GetRenderer() const -> SDL_Renderer*;
    [[nodiscard]] auto GetWindow() const -> SDL_Window*;
    auto Clear() const -> void;
    auto SetColor(COLORS::Color) const -> void;
    auto Present() const -> void;
    auto Resize() -> void;
    [[nodiscard]] auto GetWidth() const -> int;
    [[nodiscard]] auto GetHeight() const -> int;
    auto Sleep() const -> void;
    auto LoadCursors(const std::string&) -> void;
    auto SetCursor(const std::string&) -> void;
    auto GetCursor() -> SDL_Cursor*;
    auto IsOpen() const -> bool;
    auto Show() -> void;
    auto Hide() -> void;
    auto SetMenu(const std::string&, Menu*) -> void;
    auto SetCurrentMenu(const std::string&) -> void;
    auto GetCurrentMenu() const -> Menu*;
};

#endif // HERION_HERO_WINDOW_HPP
