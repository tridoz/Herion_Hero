//
// Created by tridoz on 20/05/26.
//

#ifndef HERION_HERO_BUTTONMENU_HPP
#define HERION_HERO_BUTTONMENU_HPP

#include "Menu.hpp"
#include "../../Utils/hpp/Reflector.hpp"

class ButtonMenu : public Menu {

private:
    float start_y;
    float button_y_offset;
    float center_piece_offset;


public:
    ~ButtonMenu();
    bool CheckCollision( std::vector< SDL_FRect >, float x, float y );
    void LoadConfiguration( const std::string& filepath );
    Button* GetCollisionButton( float x, float y );
    SliderSelector* GetSliderSelector( float x, float y );
    void Draw(SDL_Renderer *renderer) const;

    static constexpr auto reflect_members() {
        return concat_tuple(
            Menu::reflect_members(),
            std::make_tuple(
                Field<ButtonMenu, float>{ "start_y", &ButtonMenu::start_y },
                Field<ButtonMenu, float>{ "button_y_offset", &ButtonMenu::button_y_offset },
                Field<ButtonMenu, float>{ "center_piece_offset", &ButtonMenu::center_piece_offset }
            )
        );
    }

};


#endif //HERION_HERO_BUTTONMENU_HPP
