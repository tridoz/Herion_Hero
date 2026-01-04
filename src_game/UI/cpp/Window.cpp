//
// Created by david on 16/11/2025.
//

#include "../hpp/Window.hpp"

#include "../../Utils/hpp/JSONParser.hpp"

std::unordered_map<std::string, SDL_Cursor*> Window::Cursors;
std::string Window::current_cursor_name;

Window::Window() {
    this->window = nullptr;
    this->renderer = nullptr;
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

Window::Window( const std::string& title) {

    this->flags = 0;

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

    // Logger::LogOk(
    // std::time(nullptr),
    // "INITIALIZATION",
    // "Window",
    // "Window",
    // "SDL_INIT_VIDEO successfully initialized"
    // );

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

    // Logger::LogOk(
    //     std::time(nullptr),
    //     "CREATION",
    //     "Window",
    //     "Window",
    //     "SDL_Window successfully created"
    //     );
    SDL_SetWindowPosition( this->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED );

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

    // Logger::LogOk(
    //     std::time(nullptr),
    //     "CREATION",
    //     "Window",
    //     "Window",
    //     "SDL_Renderer successfully created"
    //     );

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

void Window::Sleep() const {
    SDL_Delay( 1000 / JSONParser::graphics::GetFrameRate() );
}

void Window::LoadCursors( const std::string &filename ) {

    std::ifstream cursors_file( "../" + filename, std::ios::in );
    std::string line;
    std::stringstream ss;

    while ( std::getline( cursors_file, line) ) {
        ss << line << std::endl;
        std::string cursor_name, cursor_path;
        int hotX, hotY;
        ss >> cursor_name >> cursor_path >> hotX >> hotY;

        ss.clear();
        SDL_Surface*  cursor_surface = IMG_Load( cursor_path.c_str() );
        Cursors[cursor_name] = SDL_CreateColorCursor( cursor_surface, hotX, hotY);
        SDL_DestroySurface( cursor_surface );

    }

}

void Window::SetCursor(const std::string &cursor_name) {
    SDL_SetCursor( Cursors[cursor_name] );
    current_cursor_name = cursor_name;
}

SDL_Cursor* Window::GetCursor() {
    return Cursors[current_cursor_name];
}
