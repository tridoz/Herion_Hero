#include "../hpp/InputProcessor.hpp"
#include <iostream>
#include "../hpp/JSONParser.hpp"

InputProcessor::InputProcessor() {
    this->player = nullptr;
    this->room_manager = nullptr;
    this->event = {0};
    this->running = true;
    this->mouse_left_pressed = false;
    this->mouse_right_pressed = false;
    this->mouse_x = 0;
    this->mouse_y = 0;
    this->key_left_pressed = false;
    this->key_right_pressed = false;
}

InputProcessor::~InputProcessor() {
    this->running = false;
}

void InputProcessor::SetEvent(SDL_Event& event) {
    this->event = event;
}

void InputProcessor::SetPlayer(Player* player) {
    this->player = player;
}

void InputProcessor::SetRoomManager(RoomManager* room_manager) {
    this->room_manager = room_manager;
}

void InputProcessor::SetMenus(std::string name, Menu* menu) {
    menus.emplace(name, menu);
}

void InputProcessor::SetTextureManager(std::string name, TextureManager *texture_manager) {
    texture_managers.emplace( name, texture_manager );
}

void InputProcessor::SetEditorRoom(EditorRoom *room) {
    this->editor_room = room;
}

void InputProcessor::SetWindowTools( std::unordered_map< std::string,  Window* > window_tools ) {
    this->window_tools = window_tools;
}

void InputProcessor::process_main_menu( int scancode ) {
    if ( scancode == SDL_SCANCODE_ESCAPE )
        this->running = false;
}

void InputProcessor::process_in_game( int scancode ) {
    switch ( scancode ) {
        case SDL_SCANCODE_ESCAPE:
            this->player->SetGameMode( Player::GameMode::PAUSE_MENU );
            break;

        case SDL_SCANCODE_UP:
            room_manager->GoUp();
            break;

        case SDL_SCANCODE_LEFT:
            room_manager->GoLeft();
            break;

        case SDL_SCANCODE_DOWN:
            room_manager->GoDown();
            break;

        case SDL_SCANCODE_RIGHT:
            room_manager->GoRight();
            break;

        case SDL_SCANCODE_D:
            key_right_pressed = true;

            break;

        case SDL_SCANCODE_A:
            key_left_pressed = true;
            break;
    }

}

void InputProcessor::process_level_editor(int scancode) {

    switch ( scancode ) {
        case SDL_SCANCODE_ESCAPE:
            this->player->SetGameMode( Player::GameMode::EDITOR_MENU ) ;
            for ( auto& [name, win] : window_tools ) {
                win->Hide();
            }
            break;

        case SDL_SCANCODE_R: {
            for ( const auto& [name, window] : window_tools ) {
                window->GetCurrentMenu()->ReloadConfiguration();
            }
            break;
        }

        case SDL_SCANCODE_T: {
            Window* texture_window = this->window_tools.at("TEXTURE_SELECTION");
            for ( const auto& [name, window] : window_tools ) {
                if ( name != "TEXTURE_SELECTION")
                    window->Hide();
            }
            if ( texture_window->IsOpen() ) {
                texture_window->Hide();
            } else {
                texture_window->Show();
            }
            break;
        }

        case SDL_SCANCODE_A: {
            Window* action_window = this->window_tools.at("ACTION_SELECTION");
            for ( const auto& [name, window] : window_tools ) {
                if ( name != "ACTION_SELECTION")
                    window->Hide();
            }
            if ( action_window->IsOpen() ) {
                action_window->Hide();
            } else {
                action_window->Show();
            }
            break;
        }

        case SDL_SCANCODE_G:
            editor_room->ToggleAxis();
            break;

        case SDL_SCANCODE_H:
            editor_room->ToggleHitboxes();
            break;

        case SDL_SCANCODE_S:
            editor_room->SaveNewEditConfiguration();
            room_manager->GenerateEditorRoom( editor_room, "../maps/room1/" );
            room_manager->GenerateRoom( RoomManager::DIRECTION::DIR_NONE, "../maps/room1/" );
            break;

        case SDL_SCANCODE_P:
            break;
    }
}

void InputProcessor::process_key_down(int scancode) {

    Player::GameMode game_mode = player->GetGameMode();

    switch ( game_mode ) {
        case Player::GameMode::MAIN_MENU:
            process_main_menu( scancode );
            break;

        case Player::GameMode::LEVEL_EDITOR:
            process_level_editor( scancode );
            break;

        case Player::GameMode::IN_GAME:
            process_in_game( scancode );
            break;
    }

}

void InputProcessor::process_key_up(const int scancode)  {
    Player::GameMode game_mode = player->GetGameMode();

    switch (scancode) {
        case SDL_SCANCODE_D:
            if ( game_mode == Player::GameMode::IN_GAME ) {
                key_right_pressed = false;
            }
            break;

        case SDL_SCANCODE_A:
            if (game_mode == Player::GameMode::IN_GAME) {
                key_left_pressed = false;
            }
        break;
    }
}

void InputProcessor::process_mouse_left_pressed() {
    SDL_GetMouseState(&mouse_x, &mouse_y);
    Button* btn;

    switch (player->GetGameMode()) {

        default:
            break;

        case Player::GameMode::MAIN_MENU:
            btn = menus.at("MAIN_MENU")->GetCollisionButton(mouse_x, mouse_y);
            if (btn != nullptr) btn->Click();
            break;

        case Player::GameMode::GENERAL_SETTINGS_MENU:
            btn = menus.at("GENERAL_SETTINGS_MENU")->GetCollisionButton(mouse_x, mouse_y);
            if (btn != nullptr) btn->Click();
            break;

        case Player::GameMode::GRAPHICS_SETTINGS_MENU:
            btn = menus.at("GRAPHICS_SETTINGS_MENU")->GetCollisionButton(mouse_x, mouse_y);
            if (btn != nullptr) btn->Click();
            break;

        case Player::GameMode::AUDIO_SETTINGS_MENU: {
            Menu* men = menus.at("AUDIO_SETTINGS_MENU");
            btn = men->GetCollisionButton(mouse_x, mouse_y);
            if (btn != nullptr) btn->Click();
            break;
        }

        case Player::GameMode::PAUSE_MENU:
            btn = menus.at("PAUSE_MENU")->GetCollisionButton(mouse_x, mouse_y);
            if (btn != nullptr) btn->Click();
            break;

        case Player::GameMode::EDITOR_MENU:
            btn = menus.at("EDITOR_MENU")->GetCollisionButton(mouse_x, mouse_y);
            if (btn != nullptr) btn->Click();
            break;

        case Player::GameMode::LEVEL_EDITOR: {

            int cell_x = static_cast<int>(mouse_x) / ( JSONParser::graphics::GetWidth() / editor_room->GetHorizontalTiles() );
            int cell_y = static_cast<int>(mouse_y) / ( JSONParser::graphics::GetHeight() / editor_room->GetVerticalTiles() );

            for ( const auto& [name, window] : window_tools ) {
                if ( name == "TEXTURE_SELECTION" ) {

                    if ( window->IsOpen() ) {
                        btn = window->GetCurrentMenu()->GetCollisionButton(mouse_x , mouse_y);
                        if ( btn != nullptr ) {
                            std::string str = btn->ClickReturn();
                            TextureManager* mng = texture_managers.at("MAIN");
                            Texture* txt = mng->GetTextureByName(str);
                            editor_room->SetCurrentEditorTexture( txt );
                        }

                    }

                } else if ( name  == "ACTION_SELECTION") {
                    if ( window->IsOpen() ) {
                        btn = window->GetCurrentMenu()->GetCollisionButton(mouse_x , mouse_y);
                        if ( btn != nullptr ) {
                            std::string str = btn->ClickReturn();
                            editor_room->SetAction( str );
                        }
                    }
                }
            }

            if ( AllWindowsClosed() ) {
                std::string action = editor_room->GetAction();
                if ( action == "add_texture" ) {

                    if ( editor_room->GetCurrentEditorTexture() != nullptr ) {
                        editor_room->GetTiles()[cell_y][cell_x]->SetTexture( editor_room->GetCurrentEditorTexture() );
                    }

                } else if ( action == "change_hitbox" ){
                    bool hitbox = editor_room->GetTiles()[cell_y][cell_x]->HasHitbox();
                    editor_room->GetTiles()[cell_y][cell_x]->SetHitbox( !hitbox );
                    editor_room->UpdateHitbox(cell_x, cell_y);
                }
            }

            break;

        }
   }

}

void InputProcessor::process_mouse_right_pressed() {
    // Non implementato
}

void InputProcessor::Process() {
    switch (this->event.type) {
        case SDL_EVENT_QUIT:
            this->running = false;
            break;

        case SDL_EVENT_KEY_DOWN:
            if (event.key.scancode < MAX_SCANCODES) {
                this->keys[event.key.scancode] = true;
                process_key_down(event.key.scancode);
            }
            break;

        case SDL_EVENT_KEY_UP:
            if (event.key.scancode < MAX_SCANCODES) {
                this->keys[event.key.scancode] = false;
                process_key_up(event.key.scancode);
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                process_mouse_left_pressed();
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                process_mouse_right_pressed();
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            break;

        case SDL_EVENT_MOUSE_WHEEL:

            if ( window_tools.at("TEXTURE_SELECTION")->IsOpen() ) {
                for ( const auto& [name, menu] : menus ) {
                    menu->SetMouseOffset( event.wheel.y);
                }
            }
    
            break;

        default:
            break;
    }
}

bool InputProcessor::ShouldQuit() const {
    return !this->running;
}

bool InputProcessor::isMouseLeftPressed() const {
    return this->mouse_left_pressed;
}

bool InputProcessor::isMouseRightPressed() const {
    return this->mouse_right_pressed;
}

void InputProcessor::update_player_movement(float delta_time) const {
    if (player->GetGameMode() != Player::GameMode::IN_GAME)
        return;

    if (key_left_pressed)
        player->Move(Player::FacingDirection::WEST, delta_time);
    else if (key_right_pressed)
        player->Move(Player::FacingDirection::EAST, delta_time);
    else
        player->SetPlayerState(Player::PlayerState::IDLE);

}

bool InputProcessor::AllWindowsClosed() {
    for ( const auto& [name, window] : window_tools ) {
        if ( window->IsOpen() ) {
            return false;
        }
    }
    return true;
}

