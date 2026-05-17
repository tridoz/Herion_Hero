//
// Created by david on 21/11/2025.
//

#ifndef HERION_HERO_BUTTON_HPP
#define HERION_HERO_BUTTON_HPP

#include <functional>
#include <SDL3/SDL.h>

#include "../../Textures/hpp/Texture.hpp"
#include "../../Utils/hpp/Logger.hpp"



class Button {
private:
    std::function<void()> onClick;

    std::vector< Texture* > textures;
    std::vector< SDL_FRect > rects ;

public:

    Button();

    void SetOnClick(std::function<void()> action);
    void Click() const;
    void SetTextures( std::vector< Texture* > textures );
    void SetRects( std::vector< SDL_FRect > rects );
    void Draw( SDL_Renderer* renderer ) const ;
    void DrawWithOffset( SDL_Renderer* renderer, const float offset_y, const float offset_x ) const ;
    std::vector< SDL_FRect > GetRects() const;
};


#endif //HERION_HERO_BUTTON_HPP