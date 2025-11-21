//
// Created by david on 21/11/2025.
//

#include "Button.hpp"

Button::Button()  = default;

void Button::SetOnClick(std::function<void()> action) {
    this->onClick = action;
}

void Button::Click() const {

    if ( onClick ) {
        onClick();
    }

}
