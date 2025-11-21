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

Window::Window( const std::string& title) {

    this->flags = SDL_WINDOW_FULLSCREEN ;

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

    Logger::LogOK(
    std::time(nullptr),
    "INITIALIZATION",
    "Window",
    "Window",
    "SDL_INIT_VIDEO successfully initialized"
    );


    const SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
    this->display_mode = SDL_GetCurrentDisplayMode( displayID );

    if ( !this->display_mode ) {
        Logger::LogErr(
            std::time(nullptr),
            "DISPLAY MODE",
            "Window",
            "Window",
            "Error while getting display mode for dimension: " + std::string(SDL_GetError() )
            );
    }

    Logger::LogOK(
        std::time(nullptr),
        "DISPLAY MODE",
        "Window",
        "Window",
        "Screen dimension retrieved correctly"
        );

    this->width = this->display_mode->w;
    this->height = this->display_mode->h;

    this->window = SDL_CreateWindow(title.c_str(), width, height, 0 /*flags*/ );

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

    this->renderer = SDL_CreateRenderer(this->window, "opengl" );
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

int Window::GetWidth() const {
    return this->width;
}

int Window::GetHeight() const {
    return this->height;
}
