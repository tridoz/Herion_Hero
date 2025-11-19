//
// Created by david on 16/11/2025.
//

#include "Window.hpp"

Window::Window() {
    this->window = nullptr;
    this->renderer = nullptr;
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

Window::Window( const int width, const int height, const std::string& title) {
    if ( !SDL_Init(SDL_INIT_VIDEO) ) {
        Logger::LogErr(
            std::time(nullptr),
            "INITIALIZATION",
            "Window",
            "Window",
            SDL_GetError()
            );
        return;
    }

    SDL_SetHint("SDL_RENDERER_SRGB", "1");


    Logger::LogOK(
        std::time(nullptr),
        "INITIALIZATION",
        "Window",
        "Window",
        "SDL_INIT_VIDEO successfully initialized"
        );

    this->window = SDL_CreateWindow(title.c_str(), width, height, 0);

    if ( !this->window ) {
        Logger::LogErr(
            std::time(nullptr),
            "CREATION",
            "Window",
            "Window",
            SDL_GetError()
            );
        return;
    }

    Logger::LogOK(
        std::time(nullptr),
        "CREATION",
        "Window",
        "Window",
        "SDL_Window successfully created"
        );

    this->renderer = SDL_CreateRenderer(this->window, "opengl");
    if ( !this->renderer ) {
        SDL_DestroyWindow(this->window);
        Logger::LogErr(
            std::time(nullptr),
            "CREATION",
            "Window",
            "Window",
            SDL_GetError()
            );
        return;
    }

    Logger::LogOK(
        std::time(nullptr),
        "CREATION",
        "Window",
        "Window",
        "SDL_Renderer successfully created"
        );

}

SDL_Renderer* Window::GetRenderer() const {
    return this->renderer;
}

SDL_Window* Window::GetWindow() const {
    return this->window;
}

void Window::Clear() const {
    SDL_RenderClear(this->renderer);
}

void Window::SetColor(const COLORS::Color color ) const {
    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
}

void Window::Present() const {
    SDL_RenderPresent( renderer );
}
