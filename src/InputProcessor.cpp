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

bool InputProcessor::isKeyPressed(const int scancode ) const {
    return keys[scancode];
}

void InputProcessor::Process()  {
    switch ( this->event.type ) {
        case SDL_EVENT_QUIT:
            this->running = false;
            break;

        case SDL_EVENT_KEY_DOWN:
            if ( event.key.scancode < MAX_SCANCODES ) {
                this->keys[event.key.scancode] = true;
            }
        break;

        case SDL_EVENT_KEY_UP:
            if ( event.key.scancode < MAX_SCANCODES ) {
                this->keys[event.key.scancode] = false;
            }
        break;

        default:
            break;
    }
}

bool InputProcessor::ShouldQuit() const {
    return this->keys[SDL_SCANCODE_ESCAPE] || !this->running;
}


bool InputProcessor::isMouseLeftPressed() const {
    return this->mouse_left_pressed;
}

bool InputProcessor::isMouseRightPressed() const {
    return this->mouse_right_pressed;
}













