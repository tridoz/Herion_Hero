//
// Created by tridoz on 20/05/26.
//

#ifndef HERION_HERO_BUTTONMENU_HPP
#define HERION_HERO_BUTTONMENU_HPP

#include "../../ParserCML/hpp/AST.hpp"
#include "../../ParserCML/hpp/Lexer.hpp"
#include "../../ParserCML/hpp/Parser.hpp"
#include "Menu.hpp"

class ButtonMenu : public Menu {

  private:
    float start_y;
    float button_y_offset;
    float center_piece_offset;
    auto BuildRow(CMLComponent, std::vector<CMLParameter>) -> void;
    auto BuildComponent(CMLComponent, std::vector<CMLParameter>) -> void;

  public:
    ButtonMenu();
    ~ButtonMenu();
    auto LoadConfiguration(const std::string&) -> void override;
    auto GetCollisionButton(float, float) -> Button* override;
    auto CheckCollision(const std::vector<SDL_FRect>&, float, float) -> bool override;
    auto GetSliderSelector(float, float) -> SliderSelector*;
    auto Draw(SDL_Renderer*) const -> void override;
};

#endif // HERION_HERO_BUTTONMENU_HPP
