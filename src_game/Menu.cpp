//
// Created by trida on 11/19/25.
//

#include "Menu.hpp"

#include "TextureManager.hpp"

Menu::Menu() {
	buttons_functions.clear();
	buttons_functions.emplace("START_GAME", ButtonsFunctions::StartGame );
	buttons_functions.emplace( "OPEN_MAIN_MENU", ButtonsFunctions::OpenMainMenu );
	buttons_functions.emplace( "OPEN_SETTINGS_MENU", ButtonsFunctions::OpenSettings );
	buttons_functions.emplace( "EXIT_GAME", ButtonsFunctions::EndGame );
	buttons_functions.emplace( "RETURN_PREVIOUS_GAME_MODE", ButtonsFunctions::ReturnPreviousState );
}

Menu::~Menu() {}

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

void Menu::LoadCfg( const std::string& filepath ) {

	std::string file_to_open = base_path + filepath;
	std::ifstream cfg_file( file_to_open, std::ios::in );

	if ( !cfg_file.is_open() ) {
		Logger::LogErr(
			std::time(nullptr),
			"CONFIGURATION",
			"Menu",
			"LoadCfg",
			"Loading cfg file [" + file_to_open + "] gone wrong : " + strerror(errno)
			);
		return;
	}

	Logger::LogOK(
		std::time(nullptr),
		"CONFIGURATION",
		"Menu",
		"LoadCfg",
		"cfg file [" + file_to_open + "] loaded correctly"
		);

	std::string line;
	std::string background_image_path;

	for ( int line_number = 0 ; std::getline( cfg_file, line ); line_number++ ) {

		if ( line.empty() ) {
			Logger::LogErr(
				std::time(nullptr),
				"CONFIGURATION",
				"Menu",
				"LoadCfg",
				"line [" + std::to_string(line_number) + "] in file [" + file_to_open + "] is empty"
				);
			continue;
		}

		if ( line_number == 0 ) {
			std::vector < std::string > tokens = split( line );
			if ( tokens.size() !=  4 ) {
				Logger::LogErr(
					std::time(nullptr),
					"CONFIGURATION",
					"Menu",
					"LoadCfg",
					"file [" + file_to_open + "] is malformed at line " + std::to_string(line_number)
					);
				return ;
			}

			this->filepath = tokens[0];
			this->start_y = std::stof( tokens[1] );
			this->button_offset = std::stof( tokens[2] );
			this->center_piece_offset = std::stof( tokens[3] );

		} else {

			std::vector < std::string > tokens = split( line );
			if ( tokens.size() !=  4) {
				Logger::LogErr(
					std::time(nullptr),
					"CONFIGURATION",
					"Menu",
					"LoadCfg",
					"file [" + file_to_open + "] is malformed at line" + std::to_string(line_number)
					);
				return ;

			}

			if ( tokens[0] == "BUTTON" ) {

				try {

					Button* btn = new Button();

					std::string text = tokens[2];
					std::vector< SDL_FRect > rects;
					std::vector< Texture > textures;

					Texture left_rect_texture = texture_manager->GetTexture( "assets/ui/buttons/button_left.png" );
					Texture	right_rect_texture = texture_manager->GetTexture( "assets/ui/buttons/button_right.png" );
					Texture center_rect_texture = texture_manager->GetTexture( "assets/ui/buttons/button_center.png" );

					textures.push_back( left_rect_texture );

					float ct_w, ct_h;
					float t_w, t_h;

					SDL_GetTextureSize( left_rect_texture.GetTexture(), &t_w, &t_h );
					SDL_FRect left_rect = { std::stof( tokens[1] ), start_y + (line_number * t_h) + (line_number*this->button_offset) , t_w, t_h };
					rects.push_back( left_rect );
					int x_offset, y_offset, width_offset, height_offset;

					for ( char c: text ) {

						Texture character;
						if ( isupper( c) ) {
							std::string path = std::string("assets/font/uppercase_letters/") + c + ".png";
							character = texture_manager->GetTexture( path );
							x_offset = 2;
							y_offset = 36;
							width_offset = -2;
							height_offset = -72;
						}else {
							std::string path = std::string("assets/font/lowercase_letters/") + c + ".png";
							character = texture_manager->GetTexture( path );
							x_offset = 4;
							y_offset = 44;
							width_offset = -4;
							height_offset = -80;
						}

						SDL_GetTextureSize( character.GetTexture(), &t_w, &t_h );
						SDL_GetTextureSize( center_rect_texture.GetTexture(), &ct_w, &ct_h );

						textures.push_back( center_rect_texture );
						textures.push_back( character );

						SDL_FRect prev = rects.at( rects.size() - 1 );
						SDL_FRect background_rect = { prev.x + prev.w, rects[0].y + this->center_piece_offset  , (t_w * 1.5f) , ct_h } ;
						SDL_FRect character_rect = { background_rect.x + x_offset,background_rect.y + y_offset, background_rect.w + width_offset, background_rect.h + height_offset  } ;

						rects.push_back( background_rect );
						rects.push_back( character_rect );

					}

					SDL_GetTextureSize( right_rect_texture.GetTexture(), &t_w, &t_h );

					SDL_FRect prev = rects.at( rects.size() - 1 );
					SDL_FRect right_rect = { prev.x + prev.w,start_y + (line_number * t_h) + (line_number * this->button_offset), t_w, t_h };

					textures.push_back( right_rect_texture );
					rects.push_back( right_rect );

					btn->SetRects( rects );
					btn->SetTextures( textures );
					btn->SetOnClick( buttons_functions.at( tokens[3] ) );

					buttons.emplace( tokens[3], btn );

				} catch ( const std::invalid_argument& e) {
					Logger::LogErr(
						std::time(nullptr),
						"CONFIGURATION",
						"Menu",
						"LoadCfg",
						"arguments at line [" + std::to_string(line_number) + "] of file [" + file_to_open + "] are in wrong format"
						);
					return;
				}

			}

		}

	}

}

void Menu::Draw( SDL_Renderer* renderer ) const {
	SDL_SetTextureBlendMode( texture_manager->GetTexture( this->filepath).GetTexture() , SDL_BLENDMODE_BLEND );
	SDL_RenderTexture( renderer, texture_manager->GetTexture( this->filepath).GetTexture(), nullptr, &background_rect );

	for ( const auto& [key, btn] : buttons ) {
		btn->Draw( renderer );
	}

}

Button* Menu::GetButton( const std::string& action )  {
	return buttons.at( action );
}

std::vector < Button* > Menu::GetButtons() {
	std::vector < Button* > vec_buttons;
	for ( const std::pair< std::string, Button*> pair : this->buttons ) {
		vec_buttons.push_back( pair.second );
	}

	return vec_buttons;
}

bool Menu::CheckCollision( std::vector<SDL_FRect> buttons, float x, float y) {
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


Button* Menu::GetCollisionButton(float x, float y) {
	for ( const std::pair< std::string, Button* > pair : this->buttons ) {
		if ( CheckCollision(pair.second->GetRects(), x, y) ) {
			return pair.second;
		}
	}

	return nullptr;
}



