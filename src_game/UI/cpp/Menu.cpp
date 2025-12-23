//
// Created by trida on 11/19/25.
//

#include "../hpp/Menu.hpp"

#include "../../Utils/hpp/JSONParser.hpp"
#include "../../Textures/hpp/TextureManager.hpp"


Menu::Menu() {
	buttons_functions.clear();
	buttons_functions.emplace("START_GAME", ButtonsFunctions::StartGame );
	buttons_functions.emplace( "OPEN_MAIN_MENU", ButtonsFunctions::OpenMainMenu );
	buttons_functions.emplace( "OPEN_SETTINGS_MENU", ButtonsFunctions::OpenSettings );
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

void Menu::LoadCfg(const std::string& cfg_filepath) {

    this->scale = JSONParser::graphics::GetScale();

    std::string file_to_open = base_path + cfg_filepath;
    std::ifstream cfg_file(file_to_open, std::ios::in);

    buttons.clear();

    if (!cfg_file.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "CONFIGURATION",
            "Menu",
            "LoadCfg",
            "Loading cfg file [" + file_to_open + "] failed: " + strerror(errno)
        );
        return;
    }

    // Logger::LogOk(
    //     std::time(nullptr),
    //     "CONFIGURATION",
    //     "Menu",
    //     "LoadCfg",
    //     "cfg file [" + file_to_open + "] loaded correctly"
    // );

    std::string line;

    int line_number = 0;
    float current_y = 0.0f;

    while (std::getline(cfg_file, line)) {

    	if (line.empty()) {
            line_number++;
            continue;
        }

        std::vector<std::string> tokens = split(line);

        // LINEA 0: CONFIG GENERALE
        if (line_number == 0) {
            if (tokens.size() != 4) {
                Logger::LogErr(
                    std::time(nullptr),
                    "CONFIGURATION",
                    "Menu",
                    "LoadCfg",
                    "Malformed cfg at line 0"
                );
                return;
            }

            this->filepath = tokens[0];
            this->start_y = std::stof(tokens[1]) * scale;
            this->button_y_offset = std::stof(tokens[2]) * scale;
            this->center_piece_offset = std::stof(tokens[3]) * scale;

            current_y = start_y;
			continue;
        }

    	if (tokens.size() == 4 ) {
            try {

                Button* btn = new Button();
                std::string text = tokens[2];

                std::vector<SDL_FRect > rects;
                std::vector<Texture* > textures;

                Texture* left_texture = texture_manager->GetTexture("assets/ui/buttons/button_left.png");
                Texture* center_texture = texture_manager->GetTexture("assets/ui/buttons/button_center.png");
                Texture* right_texture = texture_manager->GetTexture("assets/ui/buttons/button_right.png");

                textures.push_back(left_texture);

                float t_w, t_h, ct_w, ct_h;
                SDL_GetTextureSize(left_texture->GetTexture(), &t_w, &t_h);

                // Rettangolo LEFT
                SDL_FRect left_rect = { std::stof(tokens[1]) * scale, current_y, t_w * scale, t_h * scale };
                rects.push_back( left_rect);

                SDL_FRect prev = left_rect;

                // Ciclo caratteri
                for (char c : text) {

                    Texture* character;
                    float x_offset, y_offset, width_offset, height_offset;

                    if ( std::isupper(c) ) {
                        character = texture_manager->GetTexture("assets/font/uppercase_letters/" + std::string(1, c) + ".png");
                        x_offset = 2 * scale;
                        y_offset = 36 * scale;
                        width_offset = -2 * scale;
                        height_offset = -72 * scale;
                    } else if ( std::islower(c) ){
                        character = texture_manager->GetTexture("assets/font/lowercase_letters/" + std::string(1, c) + ".png");
                        x_offset = 4 * scale;
                        y_offset = 44 * scale;
                        width_offset = -4 * scale;
                        height_offset = -80 * scale;
                    } else if ( std::isdigit(c) ) {
                    	character = texture_manager->GetTexture("assets/font/numbers/" + std::string(1, c) + ".png");
                    	x_offset = 2 * scale;
                    	y_offset = 36 * scale;
                    	width_offset = -2 * scale;
                    	height_offset = -72 * scale;
                    }

                    SDL_GetTextureSize(character->GetTexture(), &t_w, &t_h);
                    SDL_GetTextureSize(center_texture->GetTexture(), &ct_w, &ct_h);

                    // Rettangolo center
                    SDL_FRect background_rect = {
                        prev.x + prev.w,
                        left_rect.y + center_piece_offset,
                        t_w * 1.5f * scale,
                        ct_h * scale
                    };

                    // Rettangolo carattere
                    SDL_FRect character_rect = {
                        background_rect.x + x_offset,
                        background_rect.y + y_offset,
                        background_rect.w + width_offset,
                        background_rect.h + height_offset
                    };

                    textures.push_back(center_texture);
                    textures.push_back(character);

                    rects.push_back( background_rect);
                    rects.push_back( character_rect);

                    prev = character_rect;
                }

                // Rettangolo RIGHT
                SDL_GetTextureSize(right_texture->GetTexture(), &t_w, &t_h);
                SDL_FRect right_rect = { prev.x + prev.w, current_y, t_w * scale, t_h * scale };
                textures.push_back(right_texture);
                rects.push_back( right_rect);

                btn->SetRects( rects );
                btn->SetTextures(textures);
                btn->SetOnClick(buttons_functions.at(tokens[3]));

                buttons.emplace(tokens[3], btn);

                // Aggiorno la posizione Y per il prossimo pulsante
                current_y += (t_h * scale) + button_y_offset;

            } catch (const std::invalid_argument&) {
                Logger::LogErr(
                    std::time(nullptr),
                    "CONFIGURATION",
                    "Menu",
                    "LoadCfg",
                    "Invalid arguments at line " + std::to_string(line_number) + " in file: " + cfg_filepath + "\n"
                );
                return;
            }
        }

        line_number++;
    }

}


void Menu::LoadCfgJson(const std::string& cfg_json_filepath) {
    this->scale = JSONParser::graphics::GetScale();
    JSONParser::menu_configuration::SetConfigFile(cfg_json_filepath);

    this->filepath = JSONParser::menu_configuration::GetBackgroundImagePath();
    this->start_y = JSONParser::menu_configuration::GetStartY();
    this->button_y_offset = JSONParser::menu_configuration::GetButtonYOffset();
    this->center_piece_offset = JSONParser::menu_configuration::GetCenterPieceOffset() * scale; // SCALING

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
            const auto fields = JSONParser::menu_configuration::GetRowElementFields(row_number, element_number);

            std::string text = (fields.type == "DYNAMIC_TEXT") ? GetText(fields.text) : fields.text;

            std::vector<SDL_FRect> rects;
            std::vector<Texture*> textures;

            Texture* left_texture   = texture_manager->GetTexture("assets/ui/buttons/button_left.png");
            Texture* center_texture = texture_manager->GetTexture("assets/ui/buttons/button_center.png");
            Texture* right_texture  = texture_manager->GetTexture("assets/ui/buttons/button_right.png");

            float left_w, left_h, center_w, center_h, right_w, right_h;
            SDL_GetTextureSize(left_texture->GetTexture(), &left_w, &left_h);
            SDL_GetTextureSize(center_texture->GetTexture(), &center_w, &center_h);
            SDL_GetTextureSize(right_texture->GetTexture(), &right_w, &right_h);

            // Rettangolo left
            SDL_FRect left_rect = { cumulative_x, current_y, left_w * scale, left_h * scale };
            rects.push_back(left_rect);
            textures.push_back(left_texture);

            // Rettangolo center: larghezza stimata testo
            float char_w = 16.0f * scale; // dimensione media carattere
            float text_total_w = text.size() * char_w;
            SDL_FRect center_rect = { cumulative_x + left_rect.w,
                                      current_y + center_piece_offset,  // center offset scalato
                                      text_total_w,
                                      center_h * scale };
            rects.push_back(center_rect);
            textures.push_back(center_texture);

            // Rettangolo right
            SDL_FRect right_rect = { center_rect.x + center_rect.w, current_y, right_w * scale, right_h * scale };
            rects.push_back(right_rect);
            textures.push_back(right_texture);

            // Centra i caratteri dentro il rettangolo center
            float char_x = center_rect.x;
            for (char c : text) {
                Texture* char_tex = nullptr;
                if (std::isupper(c))
                    char_tex = texture_manager->GetTexture("assets/font/uppercase_letters/" + std::string(1, c) + ".png");
                else if (std::islower(c))
                    char_tex = texture_manager->GetTexture("assets/font/lowercase_letters/" + std::string(1, c) + ".png");
                else if (std::isdigit(c))
                    char_tex = texture_manager->GetTexture("assets/font/numbers/" + std::string(1, c) + ".png");
                else if (isspecial(c))
                    char_tex = texture_manager->GetTexture("assets/font/special_characters/" + GetNameOfSpecialChar(c) + ".png");

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

            // Aggiorna altezza riga
            row_height = std::max({ row_height, left_rect.h, center_rect.h, right_rect.h });

            // Creazione Button o Text
            if (fields.type == "BUTTON") {
                Button* btn = new Button();
                btn->SetRects(rects);
                btn->SetTextures(textures);
                btn->SetOnClick(buttons_functions.at(fields.action.value()));
                buttons.emplace(fields.id, btn);
            } else {
                Text* txt = new Text();
                txt->SetRects(rects);
                txt->SetTextures(textures);
                texts.emplace(fields.id, txt);
            }

            cumulative_x += left_rect.w + center_rect.w + right_rect.w + button_x_offset;

        }

        current_y += row_height + button_y_offset;
    }
}


void Menu::Draw( SDL_Renderer* renderer ) const {

	SDL_SetTextureBlendMode( texture_manager->GetTexture( this->filepath)->GetTexture() , SDL_BLENDMODE_BLEND );
	SDL_RenderTexture( renderer, texture_manager->GetTexture( this->filepath)->GetTexture(), nullptr, &background_rect );

	for ( const auto& [key, btn] : buttons ) {
		btn->Draw( renderer );
	}

	for ( const auto& [key, txt] : texts ) {
		txt->Draw( renderer );
	}

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
	// Vettore di caratteri speciali
	std::vector<char> special_characters = {
		'+', '-', '*', '/', '%', '&', '|', '^', '!', '=', '<', '>', '?', '~', '@', '#', '$', '_'
	};

	// Controllo se 'c' è presente nel vettore
	return std::find(special_characters.begin(), special_characters.end(), c) != special_characters.end();
}

std::string Menu::GetNameOfSpecialChar( const char c ) {
	// Mappa dei caratteri speciali con il loro nome in CamelCase
	static const std::unordered_map<char, std::string> charNames = {
		{'+', "Plus"},
		{'-', "Minus"},
		{'*', "Asterisk"},
		{'/', "Slash"},
		{'%', "Percent"},
		{'&', "Ampersand"},
		{'|', "Pipe"},
		{'^', "Caret"},
		{'!', "Exclamation"},
		{'=', "Equals"},
		{'<', "LessThan"},
		{'>', "GreaterThan"},
		{'?', "Question"},
		{'~', "Tilde"},
		{'@', "At"},
		{'#', "Hash"},
		{'$', "Dollar"},
		{'_', "Underscore"}
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



