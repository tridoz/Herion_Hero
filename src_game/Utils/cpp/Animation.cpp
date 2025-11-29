//
// Created by trida on 11/29/25.
//

#include "../hpp/Animation.hpp"

Animation::Animation() {}

void Animation::AddFrameTexture( Texture* new_texture ) {
	animation_textures.push_back( new_texture );
}

void Animation::AddFrameRect(SDL_FRect *new_rect) {
	animation_rects.push_back( new_rect );
}

SDL_FRect *Animation::GetCurrentFrameRect() const {
	return animation_rects[current_animation_frame];
}

Texture *Animation::GetCurrentFrameTexture() const {
	return animation_textures[current_animation_frame];
}

void Animation::Update() {}

void Animation::SetFrameRate( int new_frame_rate ) {
	this->frame_rate = new_frame_rate;
	this->frame_duration = 1.0f/frame_rate;
}





