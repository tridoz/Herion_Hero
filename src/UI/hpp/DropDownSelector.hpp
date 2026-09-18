#pragma once

#include "../../UI/hpp/Button.hpp"
#include "../../UI/hpp/Text.hpp"
#include "../../Utils/hpp/Logger.hpp"

#include <functional>

class DropDownSelector {

  private:
    struct Option {
        Button* btn;
        std::function<void()> func;

        void Click() {
            func();
        }
    };

    std::vector<Option*> options;
    Text palceholder;

  public:
    enum class State : std::uint8_t { PLACEHOLDER, OPTIONS };
    State state;

    DropDownSelector();
    void CreateOption(std::vector<Renderable*>, std::function<void()>);
    void Draw();
    void ShowOptions();
    void ShowPlaceholder();
};