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
	buttons_functions.emplace( "OPEN_SETTINGS_MENU", ButtonsFunctions::OpenSettings );
	buttons_functions.emplace("OPEN_TEXTURE_SELECTION_MENU", ButtonsFunctions::OpenTextureSelectionMenu);
	buttons_functions.emplace( "OPEN_LEVEL_EDITOR", ButtonsFunctions::OpenLevelEditor );
	buttons_functions.emplace( "OPEN_ANIMATION_EDITOR", ButtonsFunctions::OpenAnimationEditor );
	buttons_functions.emplace( "EXIT_GAME", ButtonsFunctions::EndGame );
	buttons_functions.emplace( "RETURN_PREVIOUS_GAME_MODE", ButtonsFunctions::ReturnPreviousState );
	buttons_functions.emplace( "DECREASE_RESOLUTION", ButtonsFunctions::DecreaseResolution );
	buttons_functions.emplace( "INCREASE_RESOLUTION", ButtonsFunctions::IncreaseResolution );
	buttons_functions.emplace( "DECREASE_FRAME_RATE", ButtonsFunctions::DecreaseFrameLimit );
	buttons_functions.emplace( "INCREASE_FRAME_RATE", ButtonsFunctions::IncreaseFrameLimit );

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

void Menu::LoadCfg(const std::string& cfg_json_filepath) {

	try {
		JSONParser::menu_configuration::SetConfigFile(cfg_json_filepath);
	} catch ( HerionException::File::FileException &ex ) {
		ex.UpdateStackTrace( GET_CONTEXT() );
		throw;
	}

	try {
		this->type = JSONParser::menu_configuration::GetMenuType();
	} catch ( HerionException::File::FileMalformedException& ex ) {
		ex.UpdateStackTrace( GET_CONTEXT() );
		throw;
	}

	if ( this->type == "button_menu" ) {
		LoadButtonsMenuTypeConfiguration();
	} else if ( this->type == "scroll_pane_menu" ) {
		LoadScrollPaneMenuTypeConfiguration();
	} else if ( this->type == "show_pane_menu" ) {
		LoadShowPaneMenuTypeConfiguration();
	}

}

void Menu::LoadButtonsMenuTypeConfiguration() {

	try {
		this->scale = JSONParser::graphics::GetScale();
		this->filepath = JSONParser::menu_configuration::GetBackgroundImagePath();

		this->start_y = JSONParser::menu_configuration::GetStartY();
		this->button_y_offset = JSONParser::menu_configuration::GetButtonYOffset();
		this->center_piece_offset = JSONParser::menu_configuration::GetCenterPieceOffset() * scale;
	} catch ( HerionException::File::FileMalformedException& ex ) {
		ex.UpdateStackTrace( GET_CONTEXT() );
		throw;
	}

	try {
		this->background = texture_manager->GetTexture(this->filepath );
	} catch ( HerionException::File::FileException& ex ) {
		ex.UpdateStackTrace( GET_CONTEXT() );
		throw;
	}

	const int num_rows = JSONParser::menu_configuration::GetNumRows();
    float current_y = start_y;

    buttons.clear();
    texts.clear();

    for (int row_number = 0; row_number < num_rows; row_number++) {
        const int starting_x = JSONParser::menu_configuration::GetRowStartingX(row_number) * scale;
        const int button_x_offset = JSONParser::menu_configuration::GetRowButtonXOffset(row_number);
        const int num_elements = JSONParser::menu_configuration::GetRowNumElements(row_number);

        float cumulative_x = static_cast<float>(starting_x);
        float row_height = 0.0f;

        for (int element_number = 0; element_number < num_elements; element_number++) {
            const JSONParser::menu_configuration::RowElementFields menu_element_characteristic = JSONParser::menu_configuration::GetRowElementFields(row_number, element_number);

            std::string text = (menu_element_characteristic.type == "DYNAMIC_TEXT") ? GetText(menu_element_characteristic.text) : menu_element_characteristic.text;

            std::vector<SDL_FRect> rects;
            std::vector<Texture*> textures;

        	Texture* left_texture = nullptr;
        	Texture* center_texture = nullptr;
        	Texture* right_texture = nullptr;

        	try {
        		left_texture   = texture_manager->GetTexture("Assets/Ui/Buttons/ButtonLeft2.png");
        		center_texture = texture_manager->GetTexture("Assets/Ui/Buttons/ButtonCenter2.png");
        		right_texture  = texture_manager->GetTexture("Assets/Ui/Buttons/ButtonRight2.png");
        	} catch ( HerionException::File::FileNotFoundException &ex ) {
				ex.UpdateStackTrace( GET_CONTEXT() );
        		throw;
        	}

            float left_w, left_h, center_w, center_h, right_w, right_h;

            SDL_GetTextureSize(left_texture->GetTexture(), &left_w, &left_h);
            SDL_GetTextureSize(center_texture->GetTexture(), &center_w, &center_h);
            SDL_GetTextureSize(right_texture->GetTexture(), &right_w, &right_h);

            SDL_FRect left_rect = { cumulative_x, current_y, left_w * scale, left_h * scale };
            rects.push_back(left_rect);
            textures.push_back(left_texture);

            float char_w = 20.0f * scale;
            float text_total_w = text.size() * char_w;

            SDL_FRect center_rect = { cumulative_x + left_rect.w,
                                      current_y + center_piece_offset,
                                      text_total_w,
                                      center_h * scale };

            rects.push_back(center_rect);
            textures.push_back(center_texture);

            SDL_FRect right_rect = { center_rect.x + center_rect.w, current_y, right_w * scale, right_h * scale };
            rects.push_back(right_rect);
            textures.push_back(right_texture);

            float char_x = center_rect.x;

            for (char c : text) {
                Texture* char_tex = nullptr;

            	try {

            		if (std::isupper(c))
            			char_tex = texture_manager->GetTexture("Assets/Font/Game/UppercaseLetters/" + std::string(1, c) + ".png");
            		else if (std::islower(c))
            			char_tex = texture_manager->GetTexture("Assets/Font/Game/LowercaseLetters/" + std::string(1, c) + ".png");
            		else if (std::isdigit(c))
            			char_tex = texture_manager->GetTexture("Assets/Font/Game/Numbers/" + std::string(1, c) + ".png");
            		else if (isspecial(c))
            			char_tex = texture_manager->GetTexture("Assets/Font/Game/SpecialCharacters/" + GetNameOfSpecialChar(c) + ".png");
            		else if ( isspace(c))
            			char_tex = texture_manager->GetTexture("Assets/Font/Game/SpecialCharacters/space.png");

            	} catch ( HerionException::File::FileNotFoundException &ex ) {
            		ex.UpdateStackTrace( GET_CONTEXT() );
            		throw;
            	}

                float cw, ch;

                SDL_GetTextureSize(char_tex->GetTexture(), &cw, &ch);
                SDL_FRect char_rect = {
                    char_x + (char_w - cw * scale) / 2.0f,
                    center_rect.y + (center_rect.h - ch * scale) / 2.0f,
                    cw * scale,
                    ch * scale
                };
                rects.push_back(char_rect);
                textures.push_back(char_tex);

                char_x += char_w;
            }

            row_height = std::max({ row_height, left_rect.h, center_rect.h, right_rect.h });

            if (menu_element_characteristic.type == "BUTTON") {

            	Button* btn = new Button();
                btn->SetRects(rects);
                btn->SetTextures(textures);

            	if ( !buttons_functions.contains(menu_element_characteristic.action.value() ) ) {
            		THROW_FILE_NOT_FOUND( menu_element_characteristic.action.value() );
            	}

                btn->SetOnClick(buttons_functions.at(menu_element_characteristic.action.value()));
                buttons.emplace(menu_element_characteristic.id, btn);

            } else if ( menu_element_characteristic.type.contains("TEXT") ) {
                Text* txt = new Text();
                txt->SetRects(rects);
                txt->SetTextures(textures);
                texts.emplace(menu_element_characteristic.id, txt);
            }

            cumulative_x += left_rect.w + center_rect.w + right_rect.w + button_x_offset;

        }

        current_y += row_height + button_y_offset;

    }


}

void Menu::LoadScrollPaneMenuTypeConfiguration() {

	std::string cmd;

	this->background = this->texture_manager->GetTexture(JSONParser::menu_configuration::GetBackgroundImagePath() );
	float w = JSONParser::graphics::GetWidth();
	float h = JSONParser::graphics::GetHeight();

	this->background_rect = {0, 0, w, h};

	try {
		this->scale = JSONParser::graphics::GetScale();
		cmd = JSONParser::menu_configuration::GetCmd();
	} catch (HerionException::File::FileMalformedException &ex) {
		ex.UpdateStackTrace( GET_CONTEXT() );
		throw;
	}

	if ( cmd == "select_all_directory" ) {
		std::string base_directory = "../Assets/";
		CreateSubDirectories( this->directory, base_directory, 0 );
		this->buttons.clear();
		this->texts.clear();
		CreateButtonsAndTexts( this->directory );
	}

}

void Menu::CreateButtonsAndTexts( Directory* dir) {

	const int texture_size_file = JSONParser::menu_configuration::GetFileTextureSize();
	const int texture_size_directory = JSONParser::menu_configuration::GetDirectoryTextureSize();
	const int diff = texture_size_directory - texture_size_file;

	if (  dir->SubDirectory.size() == 0 ) {
		//DRAW FILES

		for ( const auto& [name, path, texture] : dir->Files ) {

			const int depth = dir->depth;
			const int previous_element_already_drawn = texts.size() + buttons.size();

			std::string right_name = name.substr(0, name.size()-4 );
			std::string right_path = path.substr(3, path.size()-3 );

			std::vector<Texture*> textures;
			std::vector<SDL_FRect> rects;

			for ( int i = 0 ; i<right_name.size() ; i++ ) {
				char c = right_name[i];

				Texture* char_tex = nullptr;
				try {

					if (std::isupper(c))
						char_tex = texture_manager->GetTexture("Assets/Font/Editor/UppercaseLetters/" + std::string(1, c) + ".png");
					else if (std::islower(c))
						char_tex = texture_manager->GetTexture("Assets/Font/Editor/LowercaseLetters/" + std::string(1, c) + ".png");
					else if (std::isdigit(c))
						char_tex = texture_manager->GetTexture("Assets/Font/Editor/Numbers/" + std::string(1, c) + ".png");
					else if (isspecial(c))
						char_tex = texture_manager->GetTexture("Assets/Font/Editor/SpecialCharacters/" + GetNameOfSpecialChar(c) + ".png");
					else if ( isspace(c))
						char_tex = texture_manager->GetTexture("Assets/Font/Editor/SpecialCharacters/space.png");

				} catch ( HerionException::File::FileNotFoundException &ex ) {
					ex.UpdateStackTrace( GET_CONTEXT() );
					throw;
				}


				SDL_FRect char_rect = {
					static_cast<float>( (depth*texture_size_file) + (texture_size_file*i + texture_size_file ) ),
					static_cast<float>( (previous_element_already_drawn*texture_size_file + texture_size_file*scale*previous_element_already_drawn)  ),
					static_cast<float>( texture_size_file*scale ),
					static_cast<float>( texture_size_file*scale )
				};
				rects.push_back(char_rect);
				textures.push_back(char_tex);
			}

			Text* txt = new Text();
			txt->SetRects(rects);
			txt->SetTextures(textures);
			texts.emplace( right_name, txt );

		}
		return;
	}

	for ( const auto& [name, dir] : dir->SubDirectory ) {

		const int depth = dir->depth;
		const int previous_element_already_drawn = texts.size() + buttons.size();

		std::vector<Texture*> textures;
		std::vector<SDL_FRect> rects;
		//DRAWING

		for ( int i = 0 ; i<name.size() ; i++ ) {
			char c = name[i];
			Texture* char_tex = nullptr;

			try {

				if (std::isupper(c))
					char_tex = texture_manager->GetTexture("Assets/Font/Editor/UppercaseLetters/" + std::string(1, c) + ".png");
				else if (std::islower(c))
					char_tex = texture_manager->GetTexture("Assets/Font/Editor/LowercaseLetters/" + std::string(1, c) + ".png");
				else if (std::isdigit(c))
					char_tex = texture_manager->GetTexture("Assets/Font/Editor/Numbers/" + std::string(1, c) + ".png");
				else if (isspecial(c))
					char_tex = texture_manager->GetTexture("Assets/Font/Editor/SpecialCharacters/" + GetNameOfSpecialChar(c) + ".png");
				else if ( isspace(c))
					char_tex = texture_manager->GetTexture("Assets/Font/Editor/SpecialCharacters/space.png");

			} catch ( HerionException::File::FileNotFoundException &ex ) {
				ex.UpdateStackTrace( GET_CONTEXT() );
				throw;
			}


			SDL_FRect char_rect = {
				static_cast<float>( (texture_size_directory*depth) + (texture_size_directory*i) ),
				static_cast<float>( (previous_element_already_drawn*texture_size_directory + texture_size_directory*scale*previous_element_already_drawn) ),
				static_cast<float>( texture_size_directory * scale ),
				static_cast<float>( texture_size_directory * scale )
			};

			rects.push_back(char_rect);
			textures.push_back(char_tex);

		}

		Text* txt = new Text();
		txt->SetRects(rects);
		txt->SetTextures(textures);
		texts.emplace(name, txt);

		CreateButtonsAndTexts( dir );

	}

}

void Menu::CreateSubDirectories( Directory*& directory, const std::string& base_directory, int depth ) {

	std::vector < std::string > cmd_output = CMD::multiline_exec( "ls " + base_directory + " | grep -v '^Font$' " );

	if ( directory == nullptr ) {
		directory = new Directory( depth, {}, {} );
	}

	if ( cmd_output.size() == 0) {
		return;
	}

	for ( const auto& output_line : cmd_output ) {
		Directory* dir = new Directory( depth+1, {}, {} );
		if ( !output_line.contains(".png") && !output_line.contains(".txt") ) {
			directory->SubDirectory.emplace( std::make_pair(output_line, dir) );
			CreateSubDirectories( dir, base_directory + output_line + "/", depth+1 );
		} else if ( output_line.contains(".png") ) {
			std::string file_name = base_directory + output_line;
			file_name = file_name.substr(3,file_name.size()-3);
			directory->Files.emplace_back( output_line, base_directory + output_line , this->texture_manager->GetTexture( file_name ) );
		}

	}

}

void Menu::LoadShowPaneMenuTypeConfiguration() {}

void Menu::Draw( SDL_Renderer* renderer ) const {

	SDL_SetTextureBlendMode( this->background->GetTexture() , SDL_BLENDMODE_BLEND );
	SDL_RenderTexture( renderer, this->background->GetTexture(), nullptr, &background_rect );

	for ( const auto& [key, btn] : buttons ) {
		if ( this->type == "scroll_pane_menu")
			btn->DrawWithOffset( renderer, mouse_offset, 0 );
		else
			btn->Draw( renderer );

	}

	for ( const auto& [key, txt] : texts ) {
		if ( this->type == "scroll_pane_menu")
			txt->DrawWithOffset( renderer, mouse_offset, 0 );
		else
			txt->Draw( renderer );
	}

}

void Menu::SetMouseOffset( float diff ) {
	this->mouse_offset += diff*4;
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
	}else {
		text = "error";
	}

	return text;
}

bool Menu::isspecial(const char c) {

	std::vector<char> special_characters = {
		'+', '-', '*', '/', '%', '&', '|', '^', '!', '=', '<', '>', '?', '~', '@', '#', '$', '_'
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
		{'_', "underscore"}
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

Button* Menu::GetCollisionButton(float x, float y) {
	for ( const std::pair< std::string, Button* > pair : this->buttons ) {
		if ( CheckCollision(pair.second->GetRects(), x, y) ) {
			return pair.second;
		}
	}

	return nullptr;
}



