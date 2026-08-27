//
// Created by david on 16/11/2025.
//

#ifndef HERION_HERO_INPUTINTERPRETER_HPP
#define HERION_HERO_INPUTINTERPRETER_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include <chrono>
#include <string>
#include <unordered_map>

#include "../../Entities/hpp/Player.hpp"
#include "../../Sound/hpp/SoundBoard.hpp"
#include "../../UI/hpp/ButtonMenu.hpp"
#include "../../UI/hpp/Menu.hpp"
#include "../../UI/hpp/ScrollPaneMenu.hpp"
#include "../../UI/hpp/Window.hpp"
#include "../../WorldBuilding/hpp/EditorRoom.hpp"
#include "../../WorldBuilding/hpp/RoomManager.hpp"

#define MAX_SCANCODES 512

class InputProcessor {

  private:
    Player* player{};
    RoomManager* room_manager{};
    SliderSelector* active_slider{};
    std::unordered_map<std::string, TextureManager*> texture_managers;
    EditorRoom* editor_room{};
    bool key_left_pressed;
    bool key_right_pressed;
    bool space_pressed;
    std::unordered_map<std::string, Window*> window_tools;
    SDL_Event event{};
    bool keys[MAX_SCANCODES] = {false};
    std::unordered_map<std::string, Menu*> menus;
    bool running;
    bool mouse_left_pressed;
    bool mouse_right_pressed;
    auto process_key_down(int) -> void;
    auto process_key_up(int) -> void;
    auto process_main_menu(int) -> void;
    auto process_animation_editor(int) -> void;
    auto process_level_editor(int) -> void;
    auto process_in_game(int) -> void;
    auto process_mouse_left_pressed() -> void;
    auto process_mouse_left_lifted() -> void;
    auto process_mouse_motion(float, float) -> void;
    auto process_mouse_right_pressed() -> void;
    auto process_mouse_right_lifted() -> void;
    auto AllWindowsClosed() -> bool;
    float mouse_x;
    float mouse_y;

  public:
    InputProcessor();
    ~InputProcessor();
    auto SetEvent(SDL_Event&) -> void;
    auto Process() -> void;
    [[nodiscard]] auto ShouldQuit() const -> bool;
    [[nodiscard]] auto isMouseLeftPressed() const -> bool;
    [[nodiscard]] auto isMouseRightPressed() const -> bool;
    auto update_player_movement(float) -> void;
    auto SetPlayer(Player*) -> void;
    auto SetRoomManager(RoomManager*) -> void;
    auto SetWindowTools(std::unordered_map<std::string, Window*>) -> void;
    auto SetMenus(std::string, Menu*) -> void;
    auto SetTextureManager(std::string, TextureManager*) -> void;
    auto SetEditorRoom(EditorRoom*) -> void;
};

#endif // HERION_HERO_INPUTINTERPRETER_HPP
