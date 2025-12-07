//
// Created by trida on 11/29/25.
//

#ifndef HERION_HERO_ANIMATION_HPP
#define HERION_HERO_ANIMATION_HPP

#include <vector>

#include "../../Textures/hpp/Texture.hpp"

class Animation {
private:

	std::vector< SDL_FRect* > animation_rects;
	std::vector < Texture* > animation_textures;

	int frame_rate;
	int frame_number;
	int current_animation_frame;
	float how_often_frame_update;
	float frame_duration;

	time_t last_update_time;
	time_t current_time;

public:
	Animation();

	void AddFrameTexture( Texture* new_texture );
	void AddFrameRect( SDL_FRect* new_rect );

	SDL_FRect* GetCurrentFrameRect() const;
	Texture* GetCurrentFrameTexture() const;

	void Update();
	void SetFrameRate( int new_frame_rate );
	void SetAnimationFrameNUmber( int new_frame_number );

};


#endif //HERION_HERO_ANIMATION_HPP