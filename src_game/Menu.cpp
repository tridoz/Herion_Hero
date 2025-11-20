//
// Created by trida on 11/19/25.
//

#include "Menu.hpp"

#include "TextureManager.hpp"

Menu::Menu() {}
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

	std::ifstream cfg_file( filepath, std::ios::in );

	if ( !cfg_file.is_open() ) {
		Logger::LogErr(
			std::time(nullptr),
			"CONFIGURATION",
			"Menu",
			"LoadCfg",
			"Loading cfg file [" + filepath + "] gone wrong : " + strerror(errno)
			);
		return;
	}

	Logger::LogOK(
		std::time(nullptr),
		"CONFIGURTION",
		"Menu",
		"LoadCfg",
		"cfg file [" + filepath + "] loaded correctly"
		);

	std::string line;
	std::string background_image_path;

	for ( int line_number = 1 ; std::getline( cfg_file, line ); line_number++ ) {

		if ( line_number == 0 ) {
			std::vector < std::string > tokens = split( line );
			if ( tokens.size() !=  3) {
				Logger::LogErr(
					std::time(nullptr),
					"CONFIGURTION",
					"Menu",
					"LoadCfg",
					"file [" + filepath + "] is malformed at line" + std::to_string(line_number)
					);
				return ;
			}

			this->filepath = tokens[0];

			try {
				// x y w h
				this->background_rect = {0, 0, std::stof(tokens[1]), std::stof(tokens[2])  };
			} catch ( const std::invalid_argument& e ) {
				Logger::LogErr(
					std::time(nullptr),
					"CONFIGURTION",
					"Menu",
					"LoadCfg",
					"arguments at line [" + std::to_string(line_number) + "] of file [" + filepath + "] are in wrong format"
					);
				return;
			}
		}

		if ( line_number != 0 ) {
			std::vector < std::string > tokens = split( line );
			if ( tokens.size() !=  7) {
				Logger::LogErr(
					std::time(nullptr),
					"CONFIGURTION",
					"Menu",
					"LoadCfg",
					"file [" + filepath + "] is malformed at line" + std::to_string(line_number)
					);
				return ;
			}

			if ( tokens[0] == "BUTTON" ) {

				try {

					Tile* tile = new Tile();
					tile->SetRect( std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4])  );
					tile->SetTexture( texture_manager->GetTexture( tokens[5]) ) ;
					buttons.push_back( tile );

				} catch ( const std::invalid_argument& e) {
					Logger::LogErr(
						std::time(nullptr),
						"CONFIGURTION",
						"Menu",
						"LoadCfg",
						"arguments at line [" + std::to_string(line_number) + "] of file [" + filepath + "] are in wrong format"
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

	for ( Tile* tile : buttons ) {
		tile->Draw( renderer );
	}

}




