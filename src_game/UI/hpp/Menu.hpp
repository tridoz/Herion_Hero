//
// Created by trida on 11/19/25.
//

#ifndef HERION_HERO_MENU_HPP
#define HERION_HERO_MENU_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>



#include "../../Textures/hpp/TextureManager.hpp"
#include "../../Utils/hpp/ButtonsFunctions.hpp"
#include "../../Utils/hpp/Logger.hpp"
#include "../../Textures/hpp/Texture.hpp"
#include "Button.hpp"
#include "Text.hpp"
#include "../../Utils/hpp/JSONParser.hpp"

class Menu {

private:
	TextureManager *texture_manager;

	std::string filepath;
	const std::string base_path = "../";
	float scale;

	SDL_FRect background_rect;

	std::unordered_map< std::string, std::function<void () > > buttons_functions;

	std::unordered_map< std::string, Button*> buttons;
	std::unordered_map< std::string, Text*> texts;


	float start_y;
	float button_y_offset;
	float center_piece_offset;

	std::vector< std::string > split( const std::string &str );

	bool CheckCollision(std::vector<SDL_FRect> buttons, float x, float y);
	void Rescale( SDL_FRect* rect );
	std::string GetText( const std::string& text_type );
	bool isspecial( const char c );
	std::string GetNameOfSpecialChar( const char c );

public:

	Menu();
	~Menu();

	void SetDimension( float w, float h);
	void SetTextureManager( TextureManager* texture_manager );
	void Draw( SDL_Renderer* renderer) const ;
	void LoadCfg(const std::string& cfg_json_filepath);
	Button* GetButton( const std::string& action ) const;
	std::vector < Button* > GetButtons() const;
	Button* GetCollisionButton ( float x, float y );

};


#endif //HERION_HERO_MENU_HPP