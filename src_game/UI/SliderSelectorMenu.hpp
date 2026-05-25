//
// Created by tridoz on 25/05/26.
//

#ifndef HERION_HERO_SLIDERSELECTORMENU_HPP
#define HERION_HERO_SLIDERSELECTORMENU_HPP
#include "hpp/Menu.hpp"


class SliderSelectorMenu : public Menu {

private:
    bool CheckCollision( std::vector<SDL_FRect> buttons, float x, float y ) override;

public :
    SliderSelectorMenu();


    Button* GetCollisionButton(float x, float y) override;
    void LoadConfiguration(const std::string &filepath) override;
    void Draw(SDL_Renderer *renderer) const override;

};


#endif //HERION_HERO_SLIDERSELECTORMENU_HPP
