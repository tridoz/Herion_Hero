//
// Created by david on 16/11/2025.
//

#include "Window.hpp"

#include "JSONParser.hpp"

Window::Window() {
    this->window = nullptr;
    this->renderer = nullptr;
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

Window::Window( const std::string& title) {

    this->flags = SDL_WINDOW_BORDERLESS  ;

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

    this->width = JSONParser::graphics::GetWidth();
    this->height = JSONParser::graphics::GetHeight();

    this->window = SDL_CreateWindow(title.c_str(), this->width, this->height, this->flags );

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

void Window::Resize() {

    this->height = JSONParser::graphics::GetHeight();
    this->width = JSONParser::graphics::GetWidth();

    SDL_SetWindowSize( this->window, this->width, this->height );
    SDL_SetWindowPosition( this->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED );
    SDL_SetRenderViewport( this->renderer, nullptr );

    JSONParser::graphics::ChangesApplied();

}

int Window::GetWidth() const {
    return this->width;
}

int Window::GetHeight() const {
    return this->height;
}
