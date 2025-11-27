//
// Created by david on 17/11/2025.
//

#include "../hpp/Tile.hpp"

Tile::Tile() {
    isWalkable = false;
    rect = {0,0,0,0 };
}

Tile::~Tile() {
    isWalkable = false;
    rect = {0,0,0,0 };
}

void Tile::SetTexture(const Texture& texture) {
    this->texture = texture;
}

SDL_FRect* Tile::GetRect() {
    return &rect;
}

void Tile::Draw(SDL_Renderer* renderer) const {
    SDL_SetTextureBlendMode( texture.GetTexture(), SDL_BLENDMODE_BLEND );
    SDL_RenderTexture( renderer, texture.GetTexture(), nullptr, &rect );
}

bool Tile::IsWalkable() const {
    return isWalkable;
}

void Tile::SetRect(float x, float y, float w, float h) {
    rect = { x,y,w,h };
}



