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
    void SetRenderables(std::vector<Renderable*> renderables);
    void Draw(SDL_Renderer* renderer) const;
    void DrawWithOffset(SDL_Renderer* renderer, const float offset_y, const float offset_x) const;
};

#endif // HERION_HERO_TEXT_HPP