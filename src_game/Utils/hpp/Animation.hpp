//
// Created by trida on 11/29/25.
//

#ifndef HERION_HERO_ANIMATION_HPP
#define HERION_HERO_ANIMATION_HPP

#include <vector>

#include "../../Textures/hpp/Texture.hpp"

class Animation {
private:

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

	Texture* GetCurrentFrameTexture() const;

	void Update();
	void SetFrameRate( int new_frame_rate );
	void SetAnimationFrameNUmber( int new_frame_number );

	float GetCurrentFrameTextureHeight() const;
	float GetCurrentFrameTextureWidth() const;
};


#endif //HERION_HERO_ANIMATION_HPP