//
// Created by tridoz on 20/05/26.
//

#ifndef HERION_HERO_BUTTONMENU_HPP
#define HERION_HERO_BUTTONMENU_HPP

#include "Menu.hpp"

class ButtonMenu : public Menu {

private:
    float start_y;
    float button_y_offset;
    float center_piece_offset;

public:
    bool CheckCollision( std::vector< SDL_FRect >, float x, float y );
    void LoadConfiguration( const std::string& filepath );
    Button* GetCollisionButton( float x, float y );
    void Draw(SDL_Renderer *renderer) const;

};


#endif //HERION_HERO_BUTTONMENU_HPP
