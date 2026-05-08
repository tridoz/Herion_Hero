//
// Created by david on 16/11/2025.
//

#ifndef HERION_HERO_INPUTINTERPRETER_HPP
#define HERION_HERO_INPUTINTERPRETER_HPP

#include <SDL3/SDL.h>

#include <unordered_map>
#include <string>
#include <chrono>

#include "../../Entities/hpp/Player.hpp"
#include "../../WorldBuilding/hpp/RoomManager.hpp"
#include "../../UI/hpp/Menu.hpp"
#include "../../UI/hpp/Window.hpp"

#define MAX_SCANCODES 512

class InputProcessor {
private:
    Player* player{};
    RoomManager* room_manager{};
    bool key_left_pressed;
    bool key_right_pressed;

    std::unordered_map < std::string,  Window* > window_tools;


    SDL_Event event{};
    bool keys[ MAX_SCANCODES ] = { false };

    std::unordered_map< std::string, Menu* > menus;

    bool running;

    bool mouse_left_pressed;
    bool mouse_right_pressed;

    void process_key_down( int scancode );
    void process_key_up( int scancode );

    void process_main_menu( int scancode );
    void process_level_editor( int scancode );
    void process_in_game( int scancode );



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
    void update_player_movement(float delta_time) const;

    void SetPlayer( Player* player );
    void SetRoomManager( RoomManager* room_manager );
    void SetWindowTools( std::unordered_map< std::string,  Window* > window_tools );

    void SetMenus( std::string name, Menu* menu );


};


#endif //HERION_HERO_INPUTINTERPRETER_HPP