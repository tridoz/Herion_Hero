//
// Created by trida on 11/19/25.
//

#include "Menu.hpp"

Menu::Menu() {}
Menu::~Menu() {}

void Menu::SetDimension(float w, float h) {
	background_rect = { 0, 0, w, h };
}

void Menu::SetTexture(const Texture texture) {
	background_texture = texture;
}

void Menu::Draw( SDL_Renderer* renderer ) const {
	SDL_SetTextureColorMod(background_texture.GetTexture(), 255, 255, 255);
	SDL_SetTextureAlphaMod(background_texture.GetTexture(), 255);
	SDL_SetTextureBlendMode( background_texture.GetTexture(), SDL_BLENDMODE_NONE );
	SDL_RenderTexture( renderer, background_texture.GetTexture(), nullptr, &background_rect );
}



