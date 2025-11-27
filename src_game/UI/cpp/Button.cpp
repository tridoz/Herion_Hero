//
// Created by david on 21/11/2025.
//

#include "../hpp/Button.hpp"

Button::Button()  = default;

void Button::SetOnClick(std::function<void()> action) {
    this->onClick = action;
}

void Button::Click() const {

    if ( onClick ) {
        onClick();
    }

}

void Button::SetTextures(std::vector<Texture> textures) {
    this->textures = textures;
}

void Button::SetRects( std::vector< SDL_FRect > rects ) {
    this->rects = rects;
}

void Button::Draw( SDL_Renderer* renderer ) const {

    for ( int i = 0; i < this->textures.size(); i++ ) {
        SDL_SetTextureBlendMode( textures[i].GetTexture(), SDL_BLENDMODE_BLEND );
        SDL_RenderTexture( renderer, textures[i].GetTexture(), nullptr, &rects[i] );
    }

}

std::vector< SDL_FRect > Button::GetRects() const {
    return rects;
}

