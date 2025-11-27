//
// Created by david on 16/11/2025.
//

#ifndef HERION_HERO_INPUTINTERPRETER_HPP
#define HERION_HERO_INPUTINTERPRETER_HPP

#include <SDL3/SDL.h>

#include <unordered_map>
#include <string>

#include "../Entities/Player.hpp"
#include "../UI/Menu.hpp"

#define MAX_SCANCODES 512

class InputProcessor {
private:
    Player* player;


    SDL_Event event{};
    bool keys[ MAX_SCANCODES ] = { false };

    std::unordered_map< std::string, Menu* > menus;

    bool running;

    bool mouse_left_pressed;
    bool mouse_right_pressed;

    void process_key_down( int scancode );

    void process_mouse_left_pressed();
    void process_mouse_right_pressed();

    float mouse_x;
    float mouse_y;

public:
    InputProcessor();
    ~InputProcessor();

    void SetEvent( SDL_Event& event );

    void Process() ;
    [[nodiscard]] bool ShouldQuit() const;
    [[nodiscard]] bool isMouseLeftPressed() const;
    [[nodiscard]] bool isMouseRightPressed() const;

    void SetPlayer( Player* player );
    void SetMenus( std::string name, Menu* menu );


};


#endif //HERION_HERO_INPUTINTERPRETER_HPP