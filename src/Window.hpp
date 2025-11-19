#ifndef HERION_HERO_WINDOW_HPP
#define HERION_HERO_WINDOW_HPP

//SDL3 INCLUDES
#include <SDL3/SDL.h>


//STD INCLUDES
#include <string>


//CUSTOM INCLUDES
#include "Logger.hpp"

class Window {

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;



public:
    Window();
    Window(const int width, const int height, const std::string& title);

    ~Window();

    [[nodiscard]] SDL_Renderer* GetRenderer() const;
    [[nodiscard]] SDL_Window* GetWindow() const;
};


#endif //HERION_HERO_WINDOW_HPP