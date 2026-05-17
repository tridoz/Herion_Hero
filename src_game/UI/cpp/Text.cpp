//
// Created by trida on 12/10/25.
//

#include "../hpp/Text.hpp"

Text::Text() {

}

void Text::SetTextures(std::vector<Texture* > textures) {
    this->textures = textures;
}

void Text::SetRects( std::vector< SDL_FRect > rects ) {
    this->rects = rects;
}

void Text::Draw( SDL_Renderer* renderer ) const {

    for ( int i = 0; i < this->textures.size(); i++ ) {
        SDL_SetTextureBlendMode( textures[i]->GetTexture(), SDL_BLENDMODE_BLEND );
        SDL_RenderTexture( renderer, textures[i]->GetTexture(), nullptr, &rects[i] );
    }

}

void Text::DrawWithOffset( SDL_Renderer* renderer, const float offset_y, const float offset_x ) const {

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
