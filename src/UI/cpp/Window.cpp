//
// Created by david on 16/11/2025.
//

#include "../hpp/Window.hpp"

#include "../../Utils/hpp/JSONParser.hpp"
#include "HerionFileException.hpp"

Window::Window() {
    this->window = nullptr;
    this->renderer = nullptr;
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    for (auto& [name, menu] : menus) {
        delete menu;
        menu = nullptr;
    }
    for (auto& [name, cursor] : Cursors) {
        SDL_DestroyCursor(cursor);
        cursor = nullptr;
    }
}

Window::Window(const std::string& title) {

    this->flags = SDL_WINDOW_FULLSCREEN;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        Logger::LogErr(std::time(nullptr), "INITIALIZATION", "Window", "Window", SDL_GetError());
        return;
    }

    try {
        this->width = JSONParser::graphics::GetWidth();
        this->height = JSONParser::graphics::GetHeight();
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    this->window = SDL_CreateWindow(title.c_str(), this->width, this->height, this->flags);

    if (!this->window) {
        Logger::LogErr(std::time(nullptr), "CREATION", "Window", "Window", SDL_GetError());
        return;
    }

    SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    this->renderer = SDL_CreateRenderer(this->window, "opengl");
    if (!this->renderer) {
        SDL_DestroyWindow(this->window);
        Logger::LogErr(std::time(nullptr), "CREATION", "Window", "Window", SDL_GetError());
        return;
    }

    this->menus = std::unordered_map<std::string, Menu*>();
    this->current_menu = nullptr;
    this->Cursors = std::unordered_map<std::string, SDL_Cursor*>();
    this->current_cursor_name = "";

    is_open = true;
}

Window::Window(const std::string& title, int width, int height) {
    this->flags = 0;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        Logger::LogErr(std::time(nullptr), "INITIALIZATION", "Window", "Window", SDL_GetError());
        return;
    }

    this->width = width;
    this->height = height;

    this->window = SDL_CreateWindow(title.c_str(), this->width, this->height, this->flags);

    if (!this->window) {
        Logger::LogErr(std::time(nullptr), "CREATION", "Window", "Window", SDL_GetError());
        return;
    }

    SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    this->renderer = SDL_CreateRenderer(this->window, "opengl");
    if (!this->renderer) {
        SDL_DestroyWindow(this->window);
        Logger::LogErr(std::time(nullptr), "CREATION", "Window", "Window", SDL_GetError());
        return;
    }

    is_open = false;
}

auto Window::GetRenderer() const -> SDL_Renderer* {
    return this->renderer;
}

auto Window::GetWindow() const -> SDL_Window* {
    return this->window;
}

auto Window::Clear() const -> void {
    SDL_RenderClear(this->renderer);
}

auto Window::SetColor(const COLORS::Color color) const -> void {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

auto Window::Present() const -> void {
    SDL_RenderPresent(renderer);
}

auto Window::Resize() -> void {

    try {
        this->height = JSONParser::graphics::GetHeight();
        this->width = JSONParser::graphics::GetWidth();
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    SDL_SetWindowSize(this->window, this->width, this->height);
    SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetRenderViewport(this->renderer, nullptr);

    JSONParser::graphics::ChangesApplied();
}

auto Window::GetWidth() const -> int {
    return this->width;
}

auto Window::GetHeight() const -> int {
    return this->height;
}

auto Window::Sleep() const -> void {
    SDL_Delay(1000 / JSONParser::graphics::GetFrameRate());
}

auto Window::LoadCursors(const std::string& filename) -> void {

    std::ifstream cursors_file("../" + filename, std::ios::in);
    std::string line;
    std::stringstream ss;

    while (std::getline(cursors_file, line)) {
        ss << line << '\n';
        std::string cursor_name, cursor_path;
        int hotX, hotY;
        ss >> cursor_name >> cursor_path >> hotX >> hotY;

        ss.clear();
        SDL_Surface* cursor_surface = IMG_Load(cursor_path.c_str());
        Cursors[cursor_name] = SDL_CreateColorCursor(cursor_surface, hotX, hotY);
        SDL_DestroySurface(cursor_surface);
    }
}

auto Window::SetCursor(const std::string& cursor_name) -> void {
    SDL_SetCursor(Cursors[cursor_name]);
    current_cursor_name = cursor_name;
}

auto Window::GetCursor() -> SDL_Cursor* {
    return Cursors[current_cursor_name];
}

auto Window::SetMenu(const std::string& name, Menu* menu_to_set) -> void {
    menus.emplace(name, menu_to_set);
}

auto Window::SetCurrentMenu(const std::string& name) -> void {
    this->current_menu = menus.at(name);
}

auto Window::GetCurrentMenu() const -> Menu* {
    return this->current_menu;
}

auto Window::IsOpen() const -> bool {
    return this->is_open;
}

auto Window::Hide() -> void {
    SDL_HideWindow(window);
    this->is_open = false;
}

auto Window::Show() -> void {
    SDL_ShowWindow(window);
    this->is_open = true;
}
