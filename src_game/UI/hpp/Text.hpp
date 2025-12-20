//
// Created by trida on 12/10/25.
//

#ifndef HERION_HERO_TEXT_HPP
#define HERION_HERO_TEXT_HPP
#include <vector>

#include "SDL3/SDL.h"


class Texture;

class Text {
private:

	std::vector< Texture* > textures;
	std::vector< SDL_FRect* > rects;


public:
	Text();


};


#endif //HERION_HERO_TEXT_HPP