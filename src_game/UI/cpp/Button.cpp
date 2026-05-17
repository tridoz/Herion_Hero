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

void Button::SetTextures(std::vector<Texture* > textures) {
    this->textures = textures;
}

void Button::SetRects( std::vector< SDL_FRect > rects ) {
    this->rects = rects;
}

void Button::Draw( SDL_Renderer* renderer ) const {

    for ( int i = 0; i < this->textures.size(); i++ ) {
        SDL_SetTextureBlendMode( textures[i]->GetTexture(), SDL_BLENDMODE_BLEND );
        SDL_RenderTexture( renderer, textures[i]->GetTexture(), nullptr, &rects[i] );
    }

}

void Button::DrawWithOffset( SDL_Renderer* renderer, const float offset_y, const float offset_x ) const {

    for ( int i = 0 ; i<this->textures.size(); i++ ) {
        Texture* texture = this->textures[i];
        SDL_FRect rect = rects[i];
        rect.x += offset_x;
        rect.y += offset_y;

        if ( rect.y >= 300 && rect.y <= 900 ) {
            SDL_SetTextureBlendMode( texture->GetTexture(), SDL_BLENDMODE_BLEND );
            SDL_RenderTexture( renderer, texture->GetTexture(), nullptr, &rect );
        }

    }

}

std::vector< SDL_FRect > Button::GetRects() const {
    return rects;
}

