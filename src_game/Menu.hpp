//
// Created by trida on 11/19/25.
//

#ifndef HERION_HERO_MENU_HPP
#define HERION_HERO_MENU_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include "TextureManager.hpp"
#include "Logger.hpp"
#include "Texture.hpp"
#include "Tile.hpp"


class Menu {

private:
	TextureManager *texture_manager;
	std::string filepath;
	SDL_FRect background_rect;

	std::vector<Tile*> buttons;

	std::vector< std::string > split( const std::string &str );

public:
	Menu();
	~Menu();

	void SetDimension( float w, float h);
	void SetTextureManager( TextureManager* texture_manager );
	void Draw( SDL_Renderer* renderer) const ;
	void LoadCfg( const std::string& filepath );

};


#endif //HERION_HERO_MENU_HPP