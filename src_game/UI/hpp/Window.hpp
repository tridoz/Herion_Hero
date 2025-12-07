#ifndef HERION_HERO_WINDOW_HPP
#define HERION_HERO_WINDOW_HPP

//SDL3 INCLUDES
#include <SDL3/SDL.h>


//STD INCLUDES
#include <string>


//CUSTOM INCLUDES
#include "../../Utils/hpp/Logger.hpp"
#include "../../Utils/hpp/COLORS.hpp"
#include "../../Utils/hpp/JSONParser.hpp"

class Window {

private:

    int flags;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    int width, height;

public:

    Window();
    Window( const std::string& title);

    ~Window();

    [[nodiscard]] SDL_Renderer* GetRenderer() const;
    [[nodiscard]] SDL_Window* GetWindow() const;

    void Clear() const;
    void SetColor( COLORS::Color ) const;
    void Present() const ;
    void Resize();

    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;

    void Sleep() const;



};


#endif //HERION_HERO_WINDOW_HPP