//
// Created by david on 16/11/2025.
//

#ifndef HERION_HERO_INPUTINTERPRETER_HPP
#define HERION_HERO_INPUTINTERPRETER_HPP

#include <SDL3/SDL.h>

#define MAX_SCANCODES 514



class InputProcessor {
private:
    SDL_Event event{};
    bool keys[ MAX_SCANCODES ] = { false };

    bool running;

    bool mouse_left_pressed;
    bool mouse_right_pressed;


    int mouse_x;
    int mouse_y;


public:
    InputProcessor();
    ~InputProcessor();

    void SetEvent( SDL_Event& event );

    void Process() ;
    [[nodiscard]] bool ShouldQuit() const;
    [[nodiscard]] bool isMouseLeftPressed() const;
    [[nodiscard]] bool isMouseRightPressed() const;

    bool isKeyPressed( int scancode ) const;

};


#endif //HERION_HERO_INPUTINTERPRETER_HPP