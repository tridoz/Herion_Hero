//
// Created by trida on 11/19/25.
//

#ifndef HERION_HERO_MENU_HPP
#define HERION_HERO_MENU_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include "TextureManager.hpp"
#include "ButtonsFunctions.hpp"
#include "Logger.hpp"
#include "Texture.hpp"
#include "Button.hpp"

class Menu {

private:
	TextureManager *texture_manager;

	std::string filepath;
	const std::string base_path = "../";

	SDL_FRect background_rect;

	std::unordered_map< std::string, std::function<void () > > buttons_functions;

	std::unordered_map< std::string, Button*> buttons;

	std::vector< std::string > split( const std::string &str );

	bool CheckCollision( SDL_FRect* button, float x, float y );

public:
	Menu();
	~Menu();

	void SetDimension( float w, float h);
	void SetTextureManager( TextureManager* texture_manager );
	void Draw( SDL_Renderer* renderer) const ;
	void LoadCfg( const std::string& filepath );
	Button* GetButton( const std::string& action );
	std::vector < Button* > GetButtons();
	Button* GetCollisionButton ( float x, float y );

};


#endif //HERION_HERO_MENU_HPP