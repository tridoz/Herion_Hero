//
// Created by david on 17/11/2025.
//

#include "../hpp/Tile.hpp"

Tile::Tile() {
    hasHitbox = false;
    rect = {0, 0, 0, 0};
}

Tile::~Tile() {
    hasHitbox = false;
    rect = {0, 0, 0, 0};
}

auto Tile::SetTexture(const Texture* new_texture) -> void {
    this->texture = new_texture;
}

auto Tile::GetRect() -> SDL_FRect* {
    return &rect;
}

auto Tile::Draw(SDL_Renderer* renderer) const -> void {
    SDL_SetTextureBlendMode(texture->GetTexture(), SDL_BLENDMODE_BLEND);
    SDL_RenderTexture(renderer, texture->GetTexture(), nullptr, &rect);
}

auto Tile::SetHitbox(bool hitbox) -> void {
    this->hasHitbox = hitbox;
}

auto Tile::HasHitbox() const -> bool {
    return hasHitbox;
}

auto Tile::SetRect(float x, float y, float w, float h) -> void {
    rect = {.x = x, .y = y, .w = w, .h = h};
}

auto Tile::GetCode() const -> std::string {
    return texture->GetCode();
}
