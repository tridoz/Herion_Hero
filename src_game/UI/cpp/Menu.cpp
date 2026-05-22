//
// Created by trida on 11/19/25.
//

#include "../hpp/Menu.hpp"

#include "../../Utils/hpp/JSONParser.hpp"
#include "../../Textures/hpp/TextureManager.hpp"


Menu::Menu() {
	buttons_functions.clear();
	buttons_functions.emplace("START_GAME", ButtonsFunctions::StartGame );
	buttons_functions.emplace( "START_NEW_GAME", ButtonsFunctions::StartNewGame );

	buttons_functions.emplace( "OPEN_MAIN_MENU", ButtonsFunctions::OpenMainMenu );
	buttons_functions.emplace("OPEN_EDITOR_MENU", ButtonsFunctions::OpenEditorMenu );
	buttons_functions.emplace( "OPEN_GENERAL_SETTINGS_MENU", ButtonsFunctions::OpenGeneralSettingsMenu );
	buttons_functions.emplace("OPEN_GRAPHICS_SETTINGS_MENU", ButtonsFunctions::OpenGraphicsSettingsMenu );
	buttons_functions.emplace("OPEN_AUDIO_SETTINGS_MENU", ButtonsFunctions::OpenAudioSettingsMenu );
	buttons_functions.emplace( "OPEN_LEVEL_EDITOR", ButtonsFunctions::OpenLevelEditor );
	buttons_functions.emplace( "OPEN_ANIMATION_EDITOR", ButtonsFunctions::OpenAnimationEditor );
	buttons_functions.emplace( "EXIT_GAME", ButtonsFunctions::EndGame );
	buttons_functions.emplace( "RETURN_PREVIOUS_GAME_MODE", ButtonsFunctions::ReturnPreviousState );

	buttons_functions.emplace( "DECREASE_RESOLUTION", ButtonsFunctions::DecreaseResolution );
	buttons_functions.emplace( "INCREASE_RESOLUTION", ButtonsFunctions::IncreaseResolution );

	buttons_functions.emplace( "DECREASE_FRAME_RATE", ButtonsFunctions::DecreaseFrameLimit );
	buttons_functions.emplace( "INCREASE_FRAME_RATE", ButtonsFunctions::IncreaseFrameLimit );

	buttons_functions.emplace("DECREASE_MASTER_VOLUME", ButtonsFunctions::DecreaseMasterVolume );
	buttons_functions.emplace("INCREASE_MASTER_VOLUME", ButtonsFunctions::IncreaseMasterVolume );

}

Menu::~Menu() {
	for ( auto button : buttons ) {
		delete button.second;
	}
}

void Menu::SetDimension(float w, float h) {
	background_rect = { 0, 0, w, h };
}

void Menu::SetTextureManager( TextureManager* texture_manager ) {
	this->texture_manager = texture_manager;
}

std::vector< std::string > Menu::split( const std::string &str ) {
	std::vector< std::string > tokens;
	std::stringstream ss(str);
	std::string token;
	while ( ss >> token ) {
		tokens.push_back(token);
	}
	return tokens;
}

void Menu::Rescale(SDL_FRect* rect) {
    rect->x *= this->scale;
    rect->y *= this->scale;
    rect->w *= this->scale;
    rect->h *= this->scale;
}


std::string Menu::GetText( const std::string& text_type ) {
	std::string text = "";

	if ( text_type == "RESOLUTION_ASPECT" ) {

		const int width = JSONParser::graphics::GetWidth();
		const int height = JSONParser::graphics::GetHeight();

		text = std::to_string(width) + "x" + std::to_string(height);
	} else if ( text_type == "FRAME_RATE" ) {
		const int frame_rate = JSONParser::graphics::GetFrameRate();
		text = std::to_string(frame_rate);
	}else if ( text_type == "MASTER_VOLUME"){
		text = std::to_string( JSONParser::audio::GetMasterVolume() );
	}

	return text;
}

bool Menu::isspecial(const char c) {

	std::vector<char> special_characters = {
		'+', '-', '*', '/', '%', '&', '|', '^', '!', '=', '<', '>', '?', '~', '@', '#', '$', '_','.'
	};

	return std::find(special_characters.begin(), special_characters.end(), c) != special_characters.end();
}

std::string Menu::GetNameOfSpecialChar( const char c ) {

	static const std::unordered_map<char, std::string> charNames = {
		{'+', "plus"},
		{'-', "minus"},
		{'*', "asterisk"},
		{'/', "slash"},
		{'%', "percent"},
		{'&', "ampersand"},
		{'|', "pipe"},
		{'^', "caret"},
		{'!', "exclamation"},
		{'=', "equals"},
		{'<', "less_than"},
		{'>', "greater_than"},
		{'?', "question"},
		{'~', "tilde"},
		{'@', "at"},
		{'#', "hash"},
		{'$', "dollar"},
		{'_', "underscore"},
		{'.', "dot"}
	};

	auto it = charNames.find(c);
	if (it != charNames.end()) {
		return it->second;  // Restituisce il nome se trovato
	} else {
		return "Unknown";   // Restituisce "Unknown" se non è un carattere speciale
	}
}

Button* Menu::GetButton( const std::string& action ) const {
	return buttons.at( action );
}

std::vector < Button* > Menu::GetButtons() const {
	std::vector < Button* > vec_buttons;
	for ( const std::pair< std::string, Button*> pair : this->buttons ) {
		vec_buttons.push_back( pair.second );
	}

	return vec_buttons;
}

bool Menu::CheckCollision( std::vector<SDL_FRect > buttons, float x, float y) {
	for ( SDL_FRect button : buttons ) {
		if (
			x >= button.x &&
			x <= button.x + button.w &&
			y >= button.y &&
			y <= button.y + button.h
		) {
			return true;
		}
	}
	return false;
}

void Menu::SetMouseOffset(float diff) {
	this->mouse_offset += diff*10;
}

void Menu::ReloadConfiguration() {
	this->LoadConfiguration( this->filepath );
}







