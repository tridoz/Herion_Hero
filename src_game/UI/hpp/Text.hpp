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

	void SetTextures( std::vector< Texture* > textures );
	void SetRects(std::vector<SDL_FRect> rects);
	void Draw( SDL_Renderer* renderer ) const ;

};


#endif //HERION_HERO_TEXT_HPP