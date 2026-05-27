//
// Created by tridoz on 22/05/26.
//

#ifndef HERION_HERO_SLIDERSELECTOR_HPP
#define HERION_HERO_SLIDERSELECTOR_HPP

#include <SDL3/SDL.h>

#include "../../Textures/hpp/Texture.hpp"
#include "../../Utils/hpp/Logger.hpp"

class SliderSelector {
private:

    std::vector < Texture* > textures;
    std::vector < SDL_FRect > rects;

    Texture* slider_button_texture;
    SDL_FRect slider_button_rect;

    Texture* slider_bar_texture;
    SDL_FRect slider_bar_rect;

    int max_value;
    int min_value;

    float max_value_x;
    float min_value_x;

    float step;

public:
    SliderSelector();

    void SetTextures( std::vector < Texture* > textures );
    void SetRects( std::vector < SDL_FRect > rects );

    void SetSliderButtonTexture( Texture* slider_texture );
    void SetSliderButtonRect( SDL_FRect slider_rect );

    void SetSliderBarTexture( Texture* slider_bar_texture );
    void SetSliderBarRect( SDL_FRect slider_rect );

    void SetMaxMinStep( const float max, const float min, const float step );
    void SetXValues( const float max, const float min );

    SDL_FRect GetSliderButtonRect();

    void Update();
    void Draw( SDL_Renderer* renderer );



};


#endif //HERION_HERO_SLIDERSELECTOR_HPP
