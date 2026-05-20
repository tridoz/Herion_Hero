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
#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "../../Textures/hpp/Texture.hpp"
#include "Button.hpp"
#include "Text.hpp"
#include "../../Utils/hpp/JSONParser.hpp"
#include "../../Utils/hpp/CMD.hpp"

class Menu {

protected:
	TextureManager *texture_manager;
	Texture* background;

	float mouse_offset;
	const std::string base_path = "../";
	float scale;

	SDL_FRect background_rect;

	std::unordered_map< std::string, std::function<void () > > buttons_functions;

	std::unordered_map< std::string, Button*> buttons;
	std::unordered_map< std::string, Text*> texts;

	std::string filepath;
	std::string type;

	void Rescale( SDL_FRect* rect );

	std::string GetText( const std::string& text_type );

	bool isspecial( const char c );

	std::string GetNameOfSpecialChar( const char c );
	std::vector< std::string > split( const std::string &str );

	virtual void LoadConfiguration( const std::string& filepath ) = 0;
	virtual bool CheckCollision(std::vector<SDL_FRect> buttons, float x, float y) = 0;


public:

	Menu();
	~Menu();

	/**
	 * @brief Set the dimension for the Menu rendering
	 * @param w Width of the menu
	 * @param h Heigth of the menu
	 */
	void SetDimension( float w, float h);

	/**
	 * @brief Set the texture_manager to gather the Texure objects while loading the menu.
	 * @param texture_manager The texture manager
	 */
	void SetTextureManager( TextureManager* texture_manager );

	/**
	 * @brief Draw the elements on the given renderer
	 * @param renderer The renderer used to draw
	 */


	/**
	 * @brief Get the Button based on a given action
	 * @param action The action need to retrieve the button
	 * @return Button*
	 */
	Button* GetButton( const std::string& action ) const;

	/**
	 * @brief Return all the buttons
	 * @return std::vector < Button* >
	 */
	std::vector < Button* > GetButtons() const;

	virtual Button* GetCollisionButton( float x, float y ) = 0;
	virtual void Draw( SDL_Renderer* renderer) const = 0 ;
	void SetMouseOffset( float diff );

};


#endif //HERION_HERO_MENU_HPP