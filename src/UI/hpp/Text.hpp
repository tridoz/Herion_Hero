//
// Created by trida on 12/10/25.
//

#ifndef HERION_HERO_TEXT_HPP
#define HERION_HERO_TEXT_HPP

#include <SDL3/SDL.h>

#include "../../Textures/hpp/Renderable.hpp"
#include "../../Utils/hpp/Logger.hpp"

class Text {
  private:
    std::vector<Renderable*> renderable;

  public:
    Text();
    auto SetRenderables(std::vector<Renderable*>) -> void;
    auto Draw(SDL_Renderer*) const -> void;
    auto DrawWithOffset(SDL_Renderer*, const float, const float) const -> void;
};

#endif // HERION_HERO_TEXT_HPP