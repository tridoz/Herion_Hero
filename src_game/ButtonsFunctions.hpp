//
// Created by david on 21/11/2025.
//

#ifndef HERION_HERO_BUTTONSFUNCTIONS_HPP
#define HERION_HERO_BUTTONSFUNCTIONS_HPP

#include "Player.hpp"


class ButtonsFunctions {
    private:
        static Player* player;

    public:
        static void StartGame();
        static void EndGame();
        static void OpenMainMenu();
        static void OpenSettings();
        static void CloseSettings();

        static void SetPlayer( Player* player );

};


#endif //HERION_HERO_BUTTONSFUNCTIONS_HPP