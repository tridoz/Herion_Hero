#include "../hpp/Renderable.hpp"

Renderable::Renderable(Texture* t, SDL_FRect* r) {
    this->texture = t;
    this->rect = r;
}

auto Renderable::GetTexture() -> Texture* {
    return texture;
}

auto Renderable::GetRect() -> SDL_FRect* {
    return rect;
}