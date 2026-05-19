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

	/**
	 * @brief Add a frame to the animation
	 * @param new_texture Frame to add
	 */
	void AddFrameTexture( Texture* new_texture );

	/**
	 * @brief Return the current animation frame
	 * @return Texture*
	 */
	Texture* GetCurrentFrameTexture() const;

	/**
	 * @brief Update the current frame
	 */
	void Update();

	/**
	 * @brief Set the frame rate for the animation
	 * @param new_frame_rate
	 */
	void SetFrameRate( int new_frame_rate );

	/**
	 * @brief Set how many frame the animation has
	 * @param new_frame_number Number of frames
	 */
	void SetAnimationFrameNUmber( int new_frame_number );

	/**
	 * @brief Return the current frame texture height
	 * @return float
	 */
	float GetCurrentFrameTextureHeight() const;

	/**
	 * @brief Return the current frame texture width
	 * @return float
	 */
	float GetCurrentFrameTextureWidth() const;
};


#endif //HERION_HERO_ANIMATION_HPP