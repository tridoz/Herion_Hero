//
// Created by trida on 12/10/25.
//

#ifndef HERION_HERO_TEXT_HPP
#define HERION_HERO_TEXT_HPP
#include <vector>

#include <SDL3/SDL.h>

#include "../../Textures/hpp/Texture.hpp"
#include "../../Utils/hpp/Logger.hpp"

class Text {
private:

	std::vector< Texture* > textures;
	std::vector< SDL_FRect > rects;


public:
	Text();

	/**
	 * @brief Set the Texture of the Text
	 * @param textures Textures to set
	 */
	void SetTextures( std::vector< Texture* > textures );

	/**
	 * @brief Set the SDL_FRects of the Text
	 * @param rects SDL_FRects to set
	 */
	void SetRects(std::vector<SDL_FRect> rects);

	/**
	 * @brief Draw the Text with its coordinates
	 * @param renderer renderer needed to draw
	 */
	void Draw( SDL_Renderer* renderer ) const ;

	/**
	 * @brief Draw the Text shifted of an offset and only if in certain coordinates
	 * @param renderer Renderer needed to draw
	 * @param offset_y Offset Y to add to the coordinates
	 * @param offset_x Offset X to add to the coodinates
	 */
	void DrawWithOffset( SDL_Renderer* renderer, const float offset_y, const float offset_x) const;

};


#endif //HERION_HERO_TEXT_HPP