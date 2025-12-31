#include "../hpp/InputProcessor.hpp"
#include <iostream>
#include "../hpp/JSONParser.hpp"

InputProcessor::InputProcessor() {
    this->event = {0};
    this->running = true;
    this->mouse_left_pressed = false;
    this->mouse_right_pressed = false;
    this->mouse_x = 0;
    this->mouse_y = 0;
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

void InputProcessor::process_key_down(int scancode) {
    Player::GameMode game_mode = player->GetGameMode();

    switch (scancode) {
        default:
            break;
            
        case SDL_SCANCODE_ESCAPE:
            switch (game_mode) {
                case Player::GameMode::MAIN_MENU:
                    running = false;
                    break;
                case Player::GameMode::IN_GAME:
                    this->player->SetGameMode(Player::GameMode::PAUSE_MENU);
                    break;

                default:
                    break;
            }
            break;

        case SDL_SCANCODE_P:
            JSONParser::graphics::IncreaseResolution();
            break;

        case SDL_SCANCODE_M:
            JSONParser::graphics::DecreaseResolution();
            break;

        case SDL_SCANCODE_UP:
            if (game_mode == Player::GameMode::IN_GAME)
                room_manager->GoUp();
            break;

        case SDL_SCANCODE_LEFT:
            if (game_mode == Player::GameMode::IN_GAME)
                room_manager->GoLeft();
            break;

        case SDL_SCANCODE_DOWN:
            if (game_mode == Player::GameMode::IN_GAME)
                room_manager->GoDown();
            break;

        case SDL_SCANCODE_RIGHT:
            if (game_mode == Player::GameMode::IN_GAME)
                room_manager->GoRight();
            break;

    }


}

void InputProcessor::process_key_up(const int scancode)  {

}

void InputProcessor::process_mouse_left_pressed() {
    SDL_GetMouseState(&mouse_x, &mouse_y);
    Button* btn;

    switch (player->GetGameMode()) {
        case Player::GameMode::MAIN_MENU:
            btn = menus.at("MAIN_MENU")->GetCollisionButton(mouse_x, mouse_y);
            if (btn != nullptr) btn->Click();
            break;

        case Player::GameMode::SETTINGS_MENU:
            btn = menus.at("SETTINGS_MENU")->GetCollisionButton(mouse_x, mouse_y);
            if (btn != nullptr) btn->Click();
            break;

        case Player::GameMode::PAUSE_MENU:
            btn = menus.at("PAUSE_MENU")->GetCollisionButton(mouse_x, mouse_y);
            if (btn != nullptr) btn->Click();
            break;

        case Player::GameMode::IN_GAME:
            float x, y;
            SDL_GetMouseState(&x, &y);
            player->Move( x, y );
        break;
    }

}

void InputProcessor::process_mouse_right_pressed() {
    // Non implementato
}

void InputProcessor::SetMenus(std::string name, Menu* menu) {
    menus.emplace(name, menu);
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
