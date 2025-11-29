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

void Menu::LoadCfg(const std::string& filepath) {
    this->scale = JSONParser::graphics::GetScale();

    std::string file_to_open = base_path + filepath;
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

    Logger::LogOK(
        std::time(nullptr),
        "CONFIGURATION",
        "Menu",
        "LoadCfg",
        "cfg file [" + file_to_open + "] loaded correctly"
    );

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
            this->button_offset = std::stof(tokens[2]) * scale;
            this->center_piece_offset = std::stof(tokens[3]) * scale;

            current_y = start_y;

        } else if (tokens.size() == 4 && tokens[0] == "BUTTON") {

            try {
                Button* btn = new Button();
                std::string text = tokens[2];

                std::vector<SDL_FRect> rects;
                std::vector<Texture> textures;

                Texture left_texture = texture_manager->GetTexture("assets/ui/buttons/button_left.png");
                Texture center_texture = texture_manager->GetTexture("assets/ui/buttons/button_center.png");
                Texture right_texture = texture_manager->GetTexture("assets/ui/buttons/button_right.png");

                textures.push_back(left_texture);

                float t_w, t_h, ct_w, ct_h;
                SDL_GetTextureSize(left_texture.GetTexture(), &t_w, &t_h);

                // Rettangolo LEFT
                SDL_FRect left_rect = { std::stof(tokens[1]) * scale, current_y, t_w * scale, t_h * scale };
                rects.push_back(left_rect);

                SDL_FRect prev = left_rect;

                // Ciclo caratteri
                for (char c : text) {

                    Texture character;
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

                    SDL_GetTextureSize(character.GetTexture(), &t_w, &t_h);
                    SDL_GetTextureSize(center_texture.GetTexture(), &ct_w, &ct_h);

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

                    rects.push_back(background_rect);
                    rects.push_back(character_rect);

                    prev = character_rect;
                }

                // Rettangolo RIGHT
                SDL_GetTextureSize(right_texture.GetTexture(), &t_w, &t_h);
                SDL_FRect right_rect = { prev.x + prev.w, current_y, t_w * scale, t_h * scale };
                textures.push_back(right_texture);
                rects.push_back(right_rect);

                btn->SetRects(rects);
                btn->SetTextures(textures);
                btn->SetOnClick(buttons_functions.at(tokens[3]));

                buttons.emplace(tokens[3], btn);

                // Aggiorno la posizione Y per il prossimo pulsante
                current_y += (t_h * scale) + button_offset;

            } catch (const std::invalid_argument&) {
                Logger::LogErr(
                    std::time(nullptr),
                    "CONFIGURATION",
                    "Menu",
                    "LoadCfg",
                    "Invalid arguments at line " + std::to_string(line_number)
                );
                return;
            }
        }

        line_number++;
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



