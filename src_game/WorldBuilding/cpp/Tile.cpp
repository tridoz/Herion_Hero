//
// Created by david on 17/11/2025.
//

#include "../hpp/Tile.hpp"

Tile::Tile() {
    hasHitbox = false;
    rect = {0,0,0,0 };
}

Tile::~Tile() {
    hasHitbox = false;
    rect = {0,0,0,0 };
}

void Tile::SetTexture(const Texture* new_texture) {
    this->texture = new_texture;
}

SDL_FRect* Tile::GetRect() {
    return &rect;
}

void Tile::Draw(SDL_Renderer* renderer) const {
    SDL_SetTextureBlendMode( texture->GetTexture(), SDL_BLENDMODE_BLEND );
    SDL_RenderTexture( renderer, texture->GetTexture(), nullptr, &rect );
}

void Tile::SetHitbox(bool hitbox) {
    this->hasHitbox = hitbox;
}

bool Tile::HasHitbox() const {
    return hasHitbox;
}

void Tile::SetRect(float x, float y, float w, float h) {
    rect = { x,y,w,h };
}

std::string Tile::GetCode() const {
    return texture->GetCode();
}



