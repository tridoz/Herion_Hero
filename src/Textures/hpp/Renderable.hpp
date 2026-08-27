#pragma once

#include "Texture.hpp";

class Renderable {
  private:
    Texture* texture;
    SDL_FRect* rect;

  public:
    Renderable();
    Renderable(Texture*, SDL_FRect*);

    auto GetTexture() -> Texture*;
    auto GetRect() -> SDL_FRect*;
};