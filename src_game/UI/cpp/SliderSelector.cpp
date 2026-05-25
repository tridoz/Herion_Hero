//
// Created by tridoz on 22/05/26.
//

#include "../hpp/SliderSelector.hpp"

SliderSelector::SliderSelector() {
    this->textures.clear();
    this->rects.clear();
    this->slider_button_rect = {};
    this->slider_button_texture = nullptr;
    this->max_value = 0;
    this->min_value = 0;
    this->max_value_x = 0;
    this->min_value_x = 0;
    this->step = 0;
}

void SliderSelector::SetRects(std::vector<SDL_FRect> rects) {
    this->rects = rects;
}
void SliderSelector::SetSliderButtonRect( SDL_FRect slider_rect ) {
    this->slider_button_rect = slider_rect;
}
void SliderSelector::SetSliderButtonTexture( Texture* slider_texture ) {
    this->slider_button_texture = slider_texture;
}
void SliderSelector::SetSliderBarRect(SDL_FRect slider_rect) {
    this->slider_bar_rect = slider_rect;
}
void SliderSelector::SetSliderBarTexture(Texture *slider_bar_texture) {
    this->slider_bar_texture = slider_bar_texture;
}
void SliderSelector::SetTextures(std::vector<Texture *> textures) {
    this->textures = textures;
}
void SliderSelector::SetMaxMinStep( const float max, const float min, const float step ) {
    this->max_value = max;
    this->min_value = min;
    this->step = step;
}
void SliderSelector::SetXValues( const float max, const float min) {
    this->max_value_x = max;
    this->min_value_x = min;
}

void SliderSelector::Draw(SDL_Renderer *renderer) {
    for ( int i = 0 ; i < this->textures.size(); i++ ) {
        SDL_SetTextureBlendMode( textures[i]->GetTexture(), SDL_BLENDMODE_BLEND );
        SDL_RenderTexture( renderer, textures[i]->GetTexture(), nullptr, &rects[i] );
    }

    SDL_SetTextureBlendMode( this->slider_bar_texture->GetTexture(), SDL_BLENDMODE_BLEND );
    SDL_RenderTexture( renderer, this->slider_bar_texture->GetTexture(), nullptr, &slider_bar_rect );

    SDL_SetTextureBlendMode( this->slider_button_texture->GetTexture(), SDL_BLENDMODE_BLEND );
    SDL_RenderTexture( renderer, this->slider_button_texture->GetTexture(), nullptr, &slider_button_rect );
}

