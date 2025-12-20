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
