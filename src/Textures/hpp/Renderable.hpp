#pragma once

#include "Texture.hpp";

class Renderable {
  private:
    Texture* texture;
    SDL_FRect* rect;

  public:
    Renderable();
    Renderable(Texture* t, SDL_FRect* r);

    Texture* GetTexture();
    SDL_FRect* GetRect();
};