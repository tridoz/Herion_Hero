//
// Created by david on 21/11/2025.
//

#ifndef HERION_HERO_BUTTON_HPP
#define HERION_HERO_BUTTON_HPP

#include <functional>

#include "Tile.hpp"


class Button : public Tile {
private:
    std::function<void()> onClick;

public:

    Button();

    void SetOnClick(std::function<void()> action);
    void Click() const;

};


#endif //HERION_HERO_BUTTON_HPP