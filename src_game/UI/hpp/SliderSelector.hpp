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

    Texture* slider_texture;
    SDL_FRect slider_rect;

    int max_value;
    int min_value;

    float max_value_x;
    float min_value_x;

    float step;

public:
    SliderSelector();




};


#endif //HERION_HERO_SLIDERSELECTOR_HPP
