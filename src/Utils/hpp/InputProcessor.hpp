//
// Created by david on 16/11/2025.
//

#ifndef HERION_HERO_INPUTINTERPRETER_HPP
#define HERION_HERO_INPUTINTERPRETER_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include <unordered_map>
#include <string>
#include <chrono>

#include "../../Entities/hpp/Player.hpp"
#include "../../WorldBuilding/hpp/RoomManager.hpp"
#include "../../UI/hpp/Menu.hpp"
#include "../../UI/hpp/ButtonMenu.hpp"
#include "../../UI/hpp/ScrollPaneMenu.hpp"
#include "../../Sound/hpp/SoundBoard.hpp"
#include "../../UI/hpp/Window.hpp"
#include "../../WorldBuilding/hpp/EditorRoom.hpp"

#define MAX_SCANCODES 512

class InputProcessor {

private:
    Player* player{};
    RoomManager* room_manager{};
    SliderSelector* active_slider{};

    std::unordered_map < std::string, TextureManager* > texture_managers;
    EditorRoom* editor_room{};

    bool key_left_pressed;
    bool key_right_pressed;
    bool space_pressed;

    std::unordered_map < std::string,  Window* > window_tools;

    SDL_Event event{};
    bool keys[ MAX_SCANCODES ] = { false };

    std::unordered_map< std::string, Menu* > menus;

    bool running;

    bool mouse_left_pressed;
    bool mouse_right_pressed;

    /**
     * @brief Process a key down event of a given key
     * @param scancode Code of the pressed key
     */
    void process_key_down( int scancode );

    /**
     * @brief Process a key up event of a given key
     * @param scancode Code of the released key
     */
    void process_key_up( int scancode );

    /**
     * @brief Process event of a given key in the Player::GameMode::MAIN_MENU
     * @param scancode Code of the key
     */
    void process_main_menu( int scancode );

    /**
     * @brief Process event of a given key in the Player::GameMode::LEVEL_EDITOR
     * @param scancode Code of the key
     */
    void process_level_editor( int scancode );

    /**
     * @brief Process event of a given key in the Player::GameMode::IN_GAME
     * @param scancode Code of the key
     */
    void process_in_game( int scancode );

    /**
     * @brief Process the event of a mouse left click
     */
    void process_mouse_left_pressed();

    void process_mouse_left_lifted();

    void process_mouse_motion( float x, float y );

    /**
     * @brief Process the event of a mouse right click
     */
    void process_mouse_right_pressed();

    void process_mouse_right_lifted();

    bool AllWindowsClosed();

    float mouse_x;
    float mouse_y;

public:
    InputProcessor();
    ~InputProcessor();

    /**
     * @brief Set the SDL_Event that needs to be checked
     * @param event
     */
    void SetEvent( SDL_Event& event );

    /**
     * Process events
     */
    void Process() ;

    /**
     * @brief Return if the program should close and terminate
     * @return bool
     */
    [[nodiscard]] bool ShouldQuit() const;

    /**
     * @brief Return if the mouse left button is pressed
     * @return bool
     */
    [[nodiscard]] bool isMouseLeftPressed() const;

    /**
     * @brief Return if the mouse right mutton is pressed
     * @return bool
     */
    [[nodiscard]] bool isMouseRightPressed() const;

    /**
     * @brief Update the player position based on input and delta time
     * @param delta_time Time elapsed beetween each frame
     */
    void update_player_movement(float delta_time);

    /**
     * @brief Set player to make changes
     * @param player Pointer to player
     */
    void SetPlayer( Player* player );

    /**
     * @brief Set room_manager to make changes
     * @param room_manager Pointer to room_manager
     */
    void SetRoomManager( RoomManager* room_manager );

    /**
     * @brief Set window_tools to make changes
     * @param window_tools window_tools to set
     */
    void SetWindowTools( std::unordered_map< std::string,  Window* > window_tools );

    /**
     * @brief Set a new menu to make changes
     * @param name Menu name
     * @param menu Menu pointer
     */
    void SetMenus( std::string name, Menu* menu );
    void SetTextureManager( std::string, TextureManager* texture_manager );
    void SetEditorRoom(EditorRoom *room);

    static constexpr auto reflect_members() {
        return std::make_tuple(
            Field<InputProcessor, Player*>{"player", &InputProcessor::player},
            Field<InputProcessor, RoomManager*>{"room_manager", &InputProcessor::room_manager},
            Field<InputProcessor, SliderSelector*>{"active_slider", &InputProcessor::active_slider},
            Field<InputProcessor, std::unordered_map<std::string, TextureManager*> >{"texture_managers", &InputProcessor::texture_managers},
            Field<InputProcessor, EditorRoom*>{"editor_room", &InputProcessor::editor_room},
            Field<InputProcessor, bool>{"key_left_pressed", &InputProcessor::key_left_pressed},
            Field<InputProcessor, bool>{"key_right_pressed", &InputProcessor::key_right_pressed},
            Field<InputProcessor, std::unordered_map< std::string,  Window* > >{"window_tools", &InputProcessor::window_tools},
            Field<InputProcessor, SDL_Event>{"event", &InputProcessor::event},
            Field<InputProcessor, bool[512]>{"keys", &InputProcessor::keys},
            Field<InputProcessor, std::unordered_map<std::string, Menu* > >{"menus", &InputProcessor::menus},
            Field<InputProcessor, bool>{"running", &InputProcessor::running},
            Field<InputProcessor, bool >{"mouse_left_pressed", &InputProcessor::mouse_left_pressed},
            Field<InputProcessor, bool>{"mouse_right_pressed", &InputProcessor::mouse_right_pressed}
        );
    }

};


#endif //HERION_HERO_INPUTINTERPRETER_HPP
