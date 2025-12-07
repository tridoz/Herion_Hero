//
// Created by trida on 11/29/25.
//

#include "../hpp/Animation.hpp"

Animation::Animation() {
	last_update_time = SDL_GetTicks();
	current_animation_frame = 0;
}

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

void Animation::Update() {
	current_time = SDL_GetTicks();
	if ( current_time - last_update_time > how_often_frame_update ) {
		current_animation_frame++;
		current_animation_frame %= animation_textures.size();
		last_update_time = current_time;
	}
}

void Animation::SetFrameRate( int new_frame_rate ) {
	this->frame_rate = new_frame_rate;
	this->how_often_frame_update = 1000.0f/frame_rate;
}

void Animation::SetAnimationFrameNUmber( int new_frame_number ) {
	this->frame_number = new_frame_number;
}





