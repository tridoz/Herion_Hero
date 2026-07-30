#include "../hpp/Renderable.hpp"

Renderable::Renderable(Texture* t, SDL_FRect* r) {
    this->texture = t;
    this->rect = r;
}

Texture* Renderable::GetTexture() {
    return texture;
}

SDL_FRect* Renderable::GetRect() {
    return rect;
}