//
// Created by trida on 11/19/25.
//

#ifndef HERION_HERO_MENU_HPP
#define HERION_HERO_MENU_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include "Texture.hpp"
#include "Logger.hpp"



class Menu {

private:
	const std::string filepath;
	SDL_FRect background_rect;
	Texture background_texture;

public:
	Menu();
	~Menu();

	void SetDimension( float w, float h);
	void SetTexture( const Texture texture );
	void Draw( SDL_Renderer* renderer) const ;

};


#endif //HERION_HERO_MENU_HPP