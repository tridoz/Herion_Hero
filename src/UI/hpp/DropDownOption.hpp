#pragma once

#include "Button.hpp"
#include "Text.hpp"

class DropDownOption {
  private:
    Button* btn;

  public:
    DropDownOption();
    auto SetButton() -> void;
    auto GetButton() -> Button*;
    auto Draw(SDL_Renderer*) -> void;
};