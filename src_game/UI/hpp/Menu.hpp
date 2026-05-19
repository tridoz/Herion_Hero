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

private:
	TextureManager *texture_manager;

	Texture* background;

	/**
	 * @struct TextureFile
	 * @brief Informations about a File
	 */
	struct TextureFile {
		/// name of the file
		std::string name;
		/// path of the file
		std::string path;
		/// texture of the file
		Texture* texture;
	};

	/**
	 * @struct Directory
	 * @brief Directory and subdirectory system
	 */
	struct Directory{
		/// depth of the subdirectory with reference to the main folder
		int depth;
		/// path of the subdirectory
		std::string path;

		/// map of all the current folder subdirectories
		std::unordered_map <
			std::string,
			Directory*
		>SubDirectory;

		/// vector for all the current folder Files
		std::vector<TextureFile> Files;

	};

	std::string filepath;
	std::string type;

	float mouse_offset;
	const std::string base_path = "../";
	float scale;

	Directory* directory;

	SDL_FRect background_rect;

	std::unordered_map< std::string, std::function<void () > > buttons_functions;

	std::unordered_map< std::string, Button*> buttons;
	std::unordered_map< std::string, Text*> texts;

	float start_y;
	float button_y_offset;
	float center_piece_offset;

	/**
	 * @brief Split the string based on single words.
	 * @param str The string that needs to be split.
	 * @return std::vector < std::string >
	 */
	std::vector< std::string > split( const std::string &str );

	/**
	 * @brief Check if the mouse coordinates when it's clicked overlap a button
	 * @param buttons The Set of all buttons to check
	 * @param x The X coordinate of the mouse
	 * @param y The Y coordinate of the mouse
	 * @return bool
	 */
	bool CheckCollision(std::vector<SDL_FRect> buttons, float x, float y);

	/**
	 * @brief Rescale a SDL_FRect based on this->scale
	 * @param rect Rectangle to rescale based
	 */
	void Rescale( SDL_FRect* rect );

	/**
	 * @brief Return the text for DYNAMIC_TEXT type in che menu configuration .json files or "error".
	 * @param text_type The type of  text (possible are "RESOLUTION_ASPECT" | "FRAME_RATE" ).
	 * @return std::string
	 */
	std::string GetText( const std::string& text_type );

	/**
	 * @brief Check if a given cahr is special (in this list)
	 * @param c Char to check if is special
	 * @return bool
	 */
	bool isspecial( const char c );

	/**
	 * @brief Return the name of the special character
	 * @param c Character to get the name of
	 * @return  std::strign
	 */
	std::string GetNameOfSpecialChar( const char c );

	/**
	 * @brief Load the menu if it is a button menu
	 */
	void LoadButtonsMenuTypeConfiguration();

	/**
	 * @brief Load the menu if it is a scroll pane menu
	 */
	void LoadScrollPaneMenuTypeConfiguration();

	/**
	 * @brief Create the Texture for the Directories and Files.
	 * @param dir The current directory that is been worked on
	 */
	void CreateButtonsAndTexts(Directory*& dir);

	/**
	 * @brief Create the sbudirectory system of the given directory
	 * @param directory current directory
	 * @param base_directory current directory path
	 * @param depth depth of current directory
	 */
	void CreateSubDirectories(Directory*& directory, const std::string &base_directory, int depth);

public:

	Menu();
	~Menu();

	/**
	 * @brief Change the mouse offset for the scroll pane rendering
	 * @param diff how much the mouse has moved
	 */
	void SetMouseOffset( float diff );

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
	void Draw( SDL_Renderer* renderer) const ;

	/**
	 * @brief Load the menu based on the path of a given .json file
	 * @param cfg_json_filepath Path of the .json loader file
	 */
	void LoadCfg(const std::string& cfg_json_filepath);

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

	/**
	 * @brief Return the button at given coordinates if there is one
	 * @param x Coordinate X of mouse
	 * @param y Coordinate Y of mouse
	 * @return Button* | nullptr
	 */
	Button* GetCollisionButton ( float x, float y );

};


#endif //HERION_HERO_MENU_HPP