//
// Created by david on 16/11/2025.
//

#include "InputProcessor.hpp"

#include <iostream>

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

void InputProcessor::SetEvent(  SDL_Event& event ) {
    this->event = event;
}

void InputProcessor::SetPlayer(Player* player) {
    this->player = player;
}

void InputProcessor::process_key_down(int scancode) {
    switch ( scancode ) {
        default:
            break;

        case SDL_SCANCODE_ESCAPE:
            switch ( player->GetGameMode() ) {
                case Player::MAIN_MENU:
                    running = false;
                    break;
                case Player::IN_GAME:
                    this->player->SetGameMode( Player::MAIN_MENU );
                    break;
            }
            break;

        case SDL_SCANCODE_P:
            switch ( player->GetGameMode() ) {
                case Player::MAIN_MENU:
                    player->SetGameMode( Player::IN_GAME );
                    break;
            }
            break;
    }

}

void InputProcessor::process_mouse_left_pressed() {

    SDL_GetMouseState( &mouse_x, &mouse_y );

    switch ( player->GetGameMode() ) {

        case Player::MAIN_MENU:
            menus.at("MAIN_MENU")->GetCollisionButton( mouse_x, mouse_y )->Click();
            break;


    }
}

void InputProcessor::process_mouse_rigth_pressed() {

}

void InputProcessor::SetMenus(std::string name, Menu* menu) {
    menus.emplace( name, menu );
}

void InputProcessor::Process()  {

    switch ( this->event.type ) {
        case SDL_EVENT_QUIT:
            this->running = false;
            break;

        case SDL_EVENT_KEY_DOWN:
            if ( event.key.scancode < MAX_SCANCODES ) {
                this->keys[event.key.scancode] = true;
                process_key_down( event.key.scancode );
            }
            break;

        case SDL_EVENT_KEY_UP:
            if ( event.key.scancode < MAX_SCANCODES ) {
                this->keys[event.key.scancode] = false;
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if ( event.button.button == SDL_BUTTON_LEFT ) {
                process_mouse_left_pressed();
            }else if ( event.button.button == SDL_BUTTON_RIGHT ) {

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













