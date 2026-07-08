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

	static constexpr auto reflect_members() {
		return std::tuple{
			Field<Animation, std::vector<Texture*>>{"animation_textures", &Animation::animation_textures},
			Field<Animation, int>{"frame_rate", &Animation::frame_rate},
			Field<Animation, int>{"frame_number", &Animation::frame_number},
			Field<Animation, int>{"current_animation_frame", &Animation::current_animation_frame},
			Field<Animation, float>{"how_often_frame_update", &Animation::how_often_frame_update},
			Field<Animation, float>{"frame_duration", &Animation::frame_duration},
			Field<Animation, time_t>{"last_update_time", &Animation::last_update_time},
			Field<Animation, time_t>{"current_time", &Animation::current_time},
		};
	}
};


#endif //HERION_HERO_ANIMATION_HPP
