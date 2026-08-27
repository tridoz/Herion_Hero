#include "../hpp/InputProcessor.hpp"
#include "../../Engine/hpp/Engine.hpp"
#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "../hpp/JSONParser.hpp"
#include "../hpp/STRINGS.hpp"
#include "Player.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_video.h"
#include "SliderSelector.hpp"
#include <cctype>
#include <iostream>

InputProcessor::InputProcessor() {
    this->player = nullptr;
    this->room_manager = nullptr;
    this->event = {0};
    this->running = true;
    this->mouse_right_pressed = false;
    this->mouse_left_pressed = false;
    this->mouse_x = 0;
    this->mouse_y = 0;
    this->key_left_pressed = false;
    this->key_right_pressed = false;
    this->editor_room = nullptr;
}

InputProcessor::~InputProcessor() {
    this->running = false;
}

auto InputProcessor::SetEvent(SDL_Event& event) -> void {
    this->event = event;
}

auto InputProcessor::SetPlayer(Player* player) -> void {
    this->player = player;
}

auto InputProcessor::SetRoomManager(RoomManager* room_manager) -> void {
    this->room_manager = room_manager;
}

auto InputProcessor::SetMenus(std::string name, Menu* menu) -> void {
    menus.emplace(name, menu);
}

auto InputProcessor::SetTextureManager(std::string name, TextureManager* texture_manager) -> void {
    texture_managers.emplace(name, texture_manager);
}

auto InputProcessor::SetEditorRoom(EditorRoom* room) -> void {
    this->editor_room = room;
}

auto InputProcessor::SetWindowTools(std::unordered_map<std::string, Window*> window_tools) -> void {
    this->window_tools = std::move(window_tools);
}

auto InputProcessor::process_main_menu(int scancode) -> void {
    if (scancode == SDL_SCANCODE_ESCAPE)
        this->running = false;
}

auto InputProcessor::process_in_game(int scancode) -> void {
    switch (scancode) {
    default:
        break;
    case SDL_SCANCODE_ESCAPE:
        Engine::SetGameState(Engine::GameState::PAUSE_MENU);
        break;

    case SDL_SCANCODE_UP:
        room_manager->GoUp();
        break;

    case SDL_SCANCODE_LEFT:
        room_manager->GoLeft();
        break;

    case SDL_SCANCODE_DOWN:
        room_manager->GoDown();
        break;

    case SDL_SCANCODE_RIGHT:
        room_manager->GoRight();
        break;

    case SDL_SCANCODE_D:
        key_right_pressed = true;
        break;

    case SDL_SCANCODE_R:
        room_manager->GenerateRoom(RoomManager::DIRECTION::DIR_NONE, "maps/room1/");
        break;

    case SDL_SCANCODE_A:
        key_left_pressed = true;
        break;

    case SDL_SCANCODE_SPACE:
    case SDL_SCANCODE_W:
        space_pressed = true;
        break;
    }
}

auto InputProcessor::process_animation_editor(int scancode) -> void {
    switch (scancode) {
    default:
        break;

    case SDL_SCANCODE_ESCAPE:
        Engine::SetGameState(Engine::GameState::EDITOR_MENU);
        break;
    }
}

auto InputProcessor::process_level_editor(int scancode) -> void {

    switch (scancode) {
    default:
        break;
    case SDL_SCANCODE_ESCAPE:
        Engine::SetGameState(Engine::GameState::EDITOR_MENU);
        for (auto& [name, win] : window_tools) {
            win->Hide();
        }
        break;

    case SDL_SCANCODE_R: {
        for (const auto& [name, window] : window_tools) {
            window->GetCurrentMenu()->ReloadConfiguration();
        }
        break;
    }

    case SDL_SCANCODE_T: {
        Window* texture_window = this->window_tools.at("TEXTURE_SELECTION");
        for (const auto& [name, window] : window_tools) {
            if (name != "TEXTURE_SELECTION")
                window->Hide();
        }
        if (texture_window->IsOpen()) {
            texture_window->Hide();
        } else {
            texture_window->Show();
        }
        break;
    }

    case SDL_SCANCODE_A: {
        Window* action_window = this->window_tools.at("ACTION_SELECTION");
        for (const auto& [name, window] : window_tools) {
            if (name != "ACTION_SELECTION")
                window->Hide();
        }
        if (action_window->IsOpen()) {
            action_window->Hide();
        } else {
            action_window->Show();
        }
        break;
    }

    case SDL_SCANCODE_E: {
        Window* entity_window = this->window_tools.at("ENTITY_SELECTION");
        for (const auto& [name, window] : window_tools) {
            if (name != "ENTITY_SELECTION")
                window->Hide();
        }
        if (entity_window->IsOpen()) {
            entity_window->Hide();
        } else {
            entity_window->Show();
        }
        break;
    }

    case SDL_SCANCODE_G:
        editor_room->ToggleAxis();
        break;

    case SDL_SCANCODE_H:
        editor_room->ToggleHitboxes();
        break;

    case SDL_SCANCODE_S:
        try {
            editor_room->SaveNewEditConfiguration();
        } catch (HerionException::File::FileException& e) {
            e.UpdateStackTrace(GET_CONTEXT());
            throw e;
        }
        room_manager->GenerateEditorRoom(editor_room, "maps/room1/");
        room_manager->GenerateRoom(RoomManager::DIRECTION::DIR_NONE, "maps/room1/");
        break;

    case SDL_SCANCODE_P:
        break;
    }
}

auto InputProcessor::process_key_down(int scancode) -> void {

    Engine::GameState game_mode = Engine::GetGameState();

    switch (game_mode) {
    case Engine::GameState::MAIN_MENU:
        process_main_menu(scancode);
        break;

    case Engine::GameState::LEVEL_EDITOR:
        process_level_editor(scancode);
        break;

    case Engine::GameState::ANIMATION_EDITOR:
        process_animation_editor(scancode);

    case Engine::GameState::IN_GAME:
        process_in_game(scancode);
        break;
    }
}

auto InputProcessor::process_key_up(const int scancode) -> void {
    Engine::GameState game_mode = Engine::GetGameState();

    switch (scancode) {
    default:
        break;
    case SDL_SCANCODE_D:
        if (game_mode == Engine::GameState::IN_GAME) {
            key_right_pressed = false;
        }
        break;

    case SDL_SCANCODE_A:
        if (game_mode == Engine::GameState::IN_GAME) {
            key_left_pressed = false;
        }
        break;
    }
}

auto InputProcessor::process_mouse_left_pressed() -> void {
    this->mouse_left_pressed = true;

    SDL_GetMouseState(&mouse_x, &mouse_y);
    Button* btn;
    SliderSelector* slider;

    switch (Engine::GetGameState()) {

    default:
        break;

    case Engine::GameState::MAIN_MENU:
        btn = menus.at(Strings::Menus::Main_Window::Names::main_menu_name)->GetCollisionButton(mouse_x, mouse_y);
        if (btn != nullptr)
            btn->Click();
        break;

    case Engine::GameState::GENERAL_SETTINGS_MENU:
        btn = menus.at(Strings::Menus::Main_Window::Names::general_settings_menu_name)
                  ->GetCollisionButton(mouse_x, mouse_y);
        if (btn != nullptr)
            btn->Click();
        break;

    case Engine::GameState::GRAPHICS_SETTINGS_MENU:
        btn = menus.at(Strings::Menus::Main_Window::Names::graphics_settings_menu_name)
                  ->GetCollisionButton(mouse_x, mouse_y);
        if (btn != nullptr)
            btn->Click();
        break;

    case Engine::GameState::AUDIO_SETTINGS_MENU: {
        btn = menus.at(Strings::Menus::Main_Window::Names::audio_settings_menu_name)
                  ->GetCollisionButton(mouse_x, mouse_y);
        if (btn != nullptr)
            btn->Click();

        ButtonMenu* bm =
            static_cast<ButtonMenu*>(menus.at(Strings::Menus::Main_Window::Names::audio_settings_menu_name));
        SliderSelector* slider = bm->GetSliderSelector(mouse_x, mouse_y);

        if (slider != nullptr) {
            active_slider = slider;
            active_slider->StartUpdating();
        }

        break;
    }

    case Engine::GameState::PAUSE_MENU:
        btn = menus.at(Strings::Menus::Main_Window::Names::pause_menu_name)->GetCollisionButton(mouse_x, mouse_y);
        if (btn != nullptr)
            btn->Click();
        break;

    case Engine::GameState::EDITOR_MENU:
        btn = menus.at(Strings::Menus::Main_Window::Names::editor_menu_name)->GetCollisionButton(mouse_x, mouse_y);
        if (btn != nullptr)
            btn->Click();
        break;

    case Engine::GameState::LEVEL_EDITOR: {

        int cell_x = static_cast<int>(mouse_x) / (JSONParser::graphics::GetWidth() / editor_room->GetHorizontalTiles());
        int cell_y = static_cast<int>(mouse_y) / (JSONParser::graphics::GetHeight() / editor_room->GetVerticalTiles());

        for (const auto& [name, window] : window_tools) {
            if (name == "TEXTURE_SELECTION") {

                if (window->IsOpen()) {
                    btn = window->GetCurrentMenu()->GetCollisionButton(mouse_x, mouse_y);
                    if (btn != nullptr) {
                        std::string str = btn->ClickReturn();
                        TextureManager* mng = texture_managers.at("MAIN");
                        Texture* txt = mng->GetTextureByName(str);
                        editor_room->SetCurrentEditorTexture(txt);
                    }
                }
            } else if (name == "ACTION_SELECTION") {
                if (window->IsOpen()) {
                    btn = window->GetCurrentMenu()->GetCollisionButton(mouse_x, mouse_y);
                    if (btn != nullptr) {
                        std::string str = btn->ClickReturn();
                        editor_room->SetAction(str);
                    }
                }
            } else if (name == "ENTITY_SELECTION") {
                if (window->IsOpen()) {
                    btn = window->GetCurrentMenu()->GetCollisionButton(mouse_x, mouse_y);
                    if (btn != nullptr) {
                        std::string str = btn->ClickReturn();
                        str = str.substr(str.find_last_of('/') + 1, str.size());
                        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
                            return std::tolower(c);
                        });
                        str = str.substr(0, str.size() - 4);
                        editor_room->SetCurrentEntityToSet(str);
                    }
                }
            }
        }

        if (AllWindowsClosed()) {
            std::string action = editor_room->GetAction();
            if (action == "add_texture") {

                if (editor_room->GetCurrentEditorTexture() != nullptr) {
                    editor_room->GetTiles()[cell_y][cell_x]->SetTexture(editor_room->GetCurrentEditorTexture());
                }
            } else if (action == "change_hitbox") {

                bool hitbox = editor_room->GetTiles()[cell_y][cell_x]->HasHitbox();
                editor_room->GetTiles()[cell_y][cell_x]->SetHitbox(!hitbox);
                editor_room->UpdateHitbox(cell_x, cell_y);
            } else if (action == "add_entity") {

                std::string entity = editor_room->GetCurrentEntity();
                std::string filepath =
                    JSONParser::entities::GetEntitiTextureFilePath("configs/entities/entities_editor.json", entity);
                int limit = JSONParser::entities::GetEntityLimit("configs/entities/entities_editor.json", entity);

                if (editor_room->GetEntitiCount(entity) >= limit && limit != -1)
                    return;

                Texture* txt = this->texture_managers.at("MAIN")->GetTextureByName(filepath);

                float w, h;
                SDL_GetTextureSize(txt->GetTexture(), &w, &h);
                SDL_FRect rect{.x = mouse_x, .y = mouse_y, .w = w, .h = h};

                Button* b = new Button();
                b->SetRenderables({new Renderable(txt, new SDL_FRect{rect})});
                b->SetOnClickReturn([b] { return b->GetText(); });

                editor_room->AddButton(b, entity);
            }
        }

        break;
    }
    }
}

auto InputProcessor::process_mouse_motion(float mouse_x, float mouse_y) -> void {

    if (active_slider == nullptr)
        return;

    if (!active_slider->IsUpdating())
        return;

    active_slider->SetOffsetX(mouse_x);
}

auto InputProcessor::process_mouse_left_lifted() -> void {
    mouse_left_pressed = false;
    Button* btn;

    switch (Engine::GetGameState()) {
    case Engine::GameState::AUDIO_SETTINGS_MENU:
        if (active_slider != nullptr && active_slider->IsUpdating()) {
            active_slider->StopUpdating();
            active_slider->SaveVolume();
            active_slider = nullptr;
        }
        break;
    }
}

auto InputProcessor::process_mouse_right_lifted() -> void {
    // TODO
}

auto InputProcessor::process_mouse_right_pressed() -> void {
    // Non implementato
}

auto InputProcessor::Process() -> void {
    switch (this->event.type) {
    case SDL_EVENT_QUIT:
        this->running = false;
        break;

    case SDL_EVENT_KEY_DOWN:
        if (event.key.scancode < MAX_SCANCODES) {
            this->keys[event.key.scancode] = true;
            process_key_down(event.key.scancode);
        }
        break;

    case SDL_EVENT_KEY_UP:
        if (event.key.scancode < MAX_SCANCODES) {
            this->keys[event.key.scancode] = false;
            process_key_up(event.key.scancode);
        }
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
            process_mouse_left_pressed();
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
            process_mouse_right_pressed();
        }
        break;

    case SDL_EVENT_MOUSE_BUTTON_UP:
        if (event.button.button == SDL_BUTTON_LEFT) {
            process_mouse_left_lifted();
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
            process_mouse_right_lifted();
        }
        break;

    case SDL_EVENT_MOUSE_MOTION:
        if (mouse_left_pressed) {
            process_mouse_motion(event.motion.x, event.motion.y);
        }
        break;

    case SDL_EVENT_MOUSE_WHEEL:

        if (window_tools.at("TEXTURE_SELECTION")->IsOpen())
            window_tools.at("TEXUTRE_SELECTION")->GetCurrentMenu()->SetMouseOffset(event.wheel.y);

        else if (window_tools.at("ENTITY_SELECTION")->IsOpen())
            window_tools.at("ENTITY_SELECTION")->GetCurrentMenu()->SetMouseOffset(event.wheel.y);

        break;

    default:
        break;
    }
}

auto InputProcessor::ShouldQuit() const -> bool {
    return !this->running;
}

auto InputProcessor::isMouseLeftPressed() const -> bool {
    return this->mouse_left_pressed;
}

auto InputProcessor::isMouseRightPressed() const -> bool {
    return this->mouse_right_pressed;
}

auto InputProcessor::update_player_movement(float delta_time) -> void {

    auto vel = player->GetComponent<ECS::Components::Velocites>();
    auto mvm = player->GetComponent<ECS::Components::MovementState>();
    auto trs = player->GetComponent<ECS::Components::Transform>();

    if (key_left_pressed) {

        vel->movement = {
            .dx = (-300 / static_cast<float>(JSONParser::graphics::GetFrameRate())),
            .dy = (vel->movement.dy / static_cast<float>(JSONParser::graphics::GetFrameRate()))
        };

        if (mvm->is_grounded)
            mvm->movement = ECS::states::Movements::RUN;

        trs->facing_direction = ECS::states::FacingDirection::LEFT;
    } else if (key_right_pressed) {

        vel->movement = {
            .dx = (300 / static_cast<float>(JSONParser::graphics::GetFrameRate())),
            .dy = (vel->movement.dy / static_cast<float>(JSONParser::graphics::GetFrameRate()))
        };

        if (mvm->is_grounded)
            mvm->movement = ECS::states::Movements::RUN;

        trs->facing_direction = ECS::states::FacingDirection::RIGHT;
    } else {

        if (mvm->is_grounded)
            mvm->movement = ECS::states::Movements::IDLE;
        vel->movement = {.dx = 0, .dy = vel->movement.dy};
    }

    if (space_pressed) {
        mvm->is_grounded = false;
        mvm->is_jumping = true;

        vel->jump = {.dx = 0, .dy = -300 / static_cast<float>(JSONParser::graphics::GetFrameRate())};
    }

    player->UpdateComponent<ECS::Components::Velocites>(vel);
    player->UpdateComponent<ECS::Components::Transform>(trs);
    player->UpdateComponent<ECS::Components::MovementState>(mvm);

    player->Move();
}

auto InputProcessor::AllWindowsClosed() -> bool {
    for (const auto& [name, window] : window_tools) {
        if (window->IsOpen()) {
            return false;
        }
    }
    return true;
}
