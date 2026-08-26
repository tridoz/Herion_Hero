#include "../hpp/Engine.hpp"
#include "STRINGS.hpp"

Engine::GameState Engine::state = Engine::GameState::MAIN_MENU;
Engine::GameState Engine::previous_state = Engine::GameState::MAIN_MENU;

Engine::Engine() {
    this->main_window = nullptr;
    this->editors_windows = {};
    this->main_texture_manager = new TextureManager();
    this->texture_selection_texture_manager = new TextureManager();
    this->action_selection_texture_manager = new TextureManager();
    this->entity_selection_texture_manager = new TextureManager();
    this->game_room_manager = new RoomManager();
    this->editor_room = new EditorRoom();
    this->img_editor = new ImageEditor();
    this->player = new Player();
    this->main_menu = new ButtonMenu();
    this->general_settings_menu = new ButtonMenu();
    this->graphics_settings_menu = new ButtonMenu();
    this->audio_settings_menu = new ButtonMenu();
    this->pause_menu = new ButtonMenu();
    this->editor_menu = new ButtonMenu();
    this->action_selection_menu = new ButtonMenu();
    this->texture_selection_menu = new ScrollPaneMenu();
    this->entity_selection_menu = new ScrollPaneMenu();
    this->processor = new InputProcessor();
}

void Engine::Init() {
    InitWindows();
    InitTextureManagers();
    InitRoomManager();
    InitMenus();
    InitInputProcessor();
    InitPlayer();

    img_editor->SetRenderer(main_window->GetRenderer());
    img_editor->SetImagePath("Assets/Entities/Player/Idle/left/frame0.png");
}

Engine::~Engine() {
    delete main_window;

    for (const auto& [editor_win_name, editor_win] : editors_windows) {
        delete editor_win;
    }

    delete main_texture_manager;
    delete texture_selection_texture_manager;
    delete action_selection_texture_manager;
    delete entity_selection_texture_manager;
    delete game_room_manager;
    delete editor_room;
    delete player;
    delete main_menu;
    delete general_settings_menu;
    delete graphics_settings_menu;
    delete audio_settings_menu;
    delete pause_menu;
    delete editor_menu;
    delete img_editor;
    delete action_selection_menu;
    delete texture_selection_menu;
    delete entity_selection_menu;
    delete processor;
}

void Engine::InitPlayer() {
    this->player->AddComponent<ECS::Components::Rendering>(
        new ECS::Components::Rendering{.renderer = main_window->GetRenderer(), .manager = main_texture_manager}
    );
    this->player->LoadSprites(Strings::Animations::Player::Paths::animation_config_file_path);
    ButtonsFunctions::SetPlayer(player);
}

void Engine::InitWindows() {

    try {
        this->main_window = new Window("Herion Hero");
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    Window* texture_selection;
    Window* action_selection;
    Window* entity_selection;

    try {
        texture_selection = new Window("Texture selection", 500, 300);
        action_selection = new Window("Action selection", 500, 300);
        entity_selection = new Window("Entity selection", 500, 300);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    this->editors_windows.emplace("TEXTURE_SELECTION", texture_selection);
    this->editors_windows.emplace("ACTION_SELECTION", action_selection);
    this->editors_windows.emplace("ENTITY_SELECTION", entity_selection);

    main_window->SetMenu(Strings::Menus::Main_Window::Names::main_menu_name, main_menu);

    main_window->SetMenu(Strings::Menus::Main_Window::Names::general_settings_menu_name, general_settings_menu);

    main_window->SetMenu(Strings::Menus::Main_Window::Names::pause_menu_name, pause_menu);

    main_window->SetMenu(Strings::Menus::Main_Window::Names::editor_menu_name, editor_menu);

    main_window->SetMenu(Strings::Menus::Main_Window::Names::graphics_settings_menu_name, graphics_settings_menu);

    main_window->SetMenu(Strings::Menus::Main_Window::Names::audio_settings_menu_name, audio_settings_menu);

    texture_selection->SetMenu("TEXTURE_SELECTION", texture_selection_menu);
    texture_selection->SetCurrentMenu("TEXTURE_SELECTION");

    action_selection->SetMenu("ACTION_SELECTION", action_selection_menu);
    action_selection->SetCurrentMenu("ACTION_SELECTION");

    entity_selection->SetMenu("ENTITY_SELECTION", entity_selection_menu);
    entity_selection->SetCurrentMenu("ENTITY_SELECTION");
}

void Engine::LoadTextureManagers() {
    try {
        main_texture_manager->LoadTextures(Strings::Textures::Paths::all_textures_path);
        texture_selection_texture_manager->LoadTextures(Strings::Textures::Paths::all_textures_path);
        action_selection_texture_manager->LoadTextures(Strings::Textures::Paths::all_textures_path);
        entity_selection_texture_manager->LoadTextures(Strings::Textures::Paths::all_textures_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }
}

void Engine::InitTextureManagers() {

    main_texture_manager->SetRenderer(main_window->GetRenderer());
    texture_selection_texture_manager->SetRenderer(editors_windows.at("TEXTURE_SELECTION")->GetRenderer());
    action_selection_texture_manager->SetRenderer(editors_windows.at("ACTION_SELECTION")->GetRenderer());
    entity_selection_texture_manager->SetRenderer(editors_windows.at("ENTITY_SELECTION")->GetRenderer());

    try {
        LoadTextureManagers();
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }
}

void Engine::InitRoomManager() {

    game_room_manager->SetTextureManager(main_texture_manager);
    game_room_manager->SetDimensions(main_window->GetWidth(), main_window->GetHeight(), 32, 18);

    try {
        game_room_manager->GenerateRoom(RoomManager::DIRECTION::DIR_NONE, "maps/room1/");
        game_room_manager->GenerateEditorRoom(editor_room, "maps/room1/");
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }
}

void Engine::LoadMenusConfigurations() {
    try {
        main_menu->LoadConfiguration(Strings::Menus::Main_Window::Paths::main_menu_config_path);
        general_settings_menu->LoadConfiguration(Strings::Menus::Main_Window::Paths::general_settings_menu_config_path);
        graphics_settings_menu->LoadConfiguration(
            Strings::Menus::Main_Window::Paths::graphics_settings_menu_config_path
        );
        audio_settings_menu->LoadConfiguration(Strings::Menus::Main_Window::Paths::audio_settings_menu_config_path);
        pause_menu->LoadConfiguration(Strings::Menus::Main_Window::Paths::pause_menu_config_path);
        editor_menu->LoadConfiguration(Strings::Menus::Main_Window::Paths::editor_menu_config_path);
        texture_selection_menu->LoadConfiguration(
            Strings::Menus::Level_Editors_Window::Paths::texture_selection_menu_config_path
        );
        action_selection_menu->LoadConfiguration(
            Strings::Menus::Level_Editors_Window::Paths::action_selection_menu_config_path
        );
        entity_selection_menu->LoadConfiguration(
            Strings::Menus::Level_Editors_Window::Paths::entity_selection_menu_config_path
        );
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }
}

void Engine::SetMenusDimensions() {
    main_menu->SetTextureManager(main_texture_manager);
    main_menu->SetDimension(static_cast<float>(main_window->GetWidth()), static_cast<float>(main_window->GetHeight()));

    general_settings_menu->SetTextureManager(main_texture_manager);
    general_settings_menu->SetDimension(
        static_cast<float>(main_window->GetWidth()), static_cast<float>(main_window->GetHeight())
    );

    graphics_settings_menu->SetTextureManager(main_texture_manager);
    graphics_settings_menu->SetDimension(
        static_cast<float>(main_window->GetWidth()), static_cast<float>(main_window->GetHeight())
    );

    audio_settings_menu->SetTextureManager(main_texture_manager);
    audio_settings_menu->SetDimension(
        static_cast<float>(main_window->GetWidth()), static_cast<float>(main_window->GetHeight())
    );

    pause_menu->SetTextureManager(main_texture_manager);
    pause_menu->SetDimension(static_cast<float>(main_window->GetWidth()), static_cast<float>(main_window->GetHeight()));

    editor_menu->SetTextureManager(main_texture_manager);
    editor_menu->SetDimension(
        static_cast<float>(main_window->GetWidth()), static_cast<float>(main_window->GetHeight())
    );

    texture_selection_menu->SetTextureManager(texture_selection_texture_manager);
    texture_selection_menu->SetDimension(
        static_cast<float>(editors_windows.at("TEXTURE_SELECTION")->GetWidth()),
        static_cast<float>(editors_windows.at("TEXTURE_SELECTION")->GetHeight())
    );

    action_selection_menu->SetTextureManager(action_selection_texture_manager);
    action_selection_menu->SetDimension(
        static_cast<float>(editors_windows.at("ACTION_SELECTION")->GetWidth()),
        static_cast<float>(editors_windows.at("ACTION_SELECTION")->GetHeight())
    );

    entity_selection_menu->SetTextureManager(entity_selection_texture_manager);
    entity_selection_menu->SetDimension(
        static_cast<float>(editors_windows.at("ENTITY_SELECTION")->GetWidth()),
        static_cast<float>(editors_windows.at("ENTITY_SELECTION")->GetHeight())
    );
}

void Engine::InitMenus() {

    SetMenusDimensions();

    try {
        LoadMenusConfigurations();
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }
}

void Engine::InitInputProcessor() {
    processor->SetMenus(Strings::Menus::Main_Window::Names::main_menu_name, main_menu);

    processor->SetMenus(Strings::Menus::Main_Window::Names::general_settings_menu_name, general_settings_menu);

    processor->SetMenus(Strings::Menus::Main_Window::Names::graphics_settings_menu_name, graphics_settings_menu);

    processor->SetMenus(Strings::Menus::Main_Window::Names::audio_settings_menu_name, audio_settings_menu);

    processor->SetMenus(Strings::Menus::Main_Window::Names::pause_menu_name, pause_menu);

    processor->SetMenus(Strings::Menus::Main_Window::Names::editor_menu_name, editor_menu);

    processor->SetMenus(
        Strings::Menus::Level_Editors_Window::Names::texture_selection_menu_name, texture_selection_menu
    );

    processor->SetMenus(Strings::Menus::Level_Editors_Window::Names::action_selection_menu_name, action_selection_menu);

    processor->SetMenus(Strings::Menus::Level_Editors_Window::Names::entity_selection_menu_name, entity_selection_menu);

    processor->SetTextureManager(Strings::TextureManagers::Names::main_texture_manager_name, main_texture_manager);

    processor->SetTextureManager(
        Strings::TextureManagers::Names::texture_selection_menu_name, texture_selection_texture_manager
    );

    processor->SetTextureManager(
        Strings::TextureManagers::Names::action_selection_menu_name, action_selection_texture_manager
    );

    processor->SetTextureManager(
        Strings::TextureManagers::Names::entity_seleciton_menu_name, entity_selection_texture_manager
    );

    processor->SetEditorRoom(editor_room);
    processor->SetWindowTools(editors_windows);
    processor->SetPlayer(player);
    processor->SetRoomManager(game_room_manager);
    player->SetTextureManager(main_texture_manager);
}

void Engine::Run() {

    SDL_Event event;
    Uint32 last_frame_time = SDL_GetTicks();

    while (!processor->ShouldQuit() && GetGameState() != Engine::GameState::EXIT) {

        Uint32 current_time = SDL_GetTicks();
        deltaTime = static_cast<float>(current_time - last_frame_time) / 1000.0F;
        last_frame_time = current_time;

        deltaTime = std::clamp(deltaTime, 0.0F, 0.033F);

        player->SetDeltaTime(deltaTime);

        while (SDL_PollEvent(&event)) {
            processor->SetEvent(event);
            try {
                processor->Process();
            } catch (HerionException::File::FileException& e) {
                e.UpdateStackTrace(GET_CONTEXT());
                Logger::LogStackTrace(std::time(nullptr), e.GetStackTrace());
                return;
            }
        }

        if (JSONParser::graphics::changed) {
            main_window->Resize();
            SetMenusDimensions();
            try {
                LoadMenusConfigurations();
            } catch (HerionException::File::FileException& ex) {
                ex.UpdateStackTrace(GET_CONTEXT());
                throw;
            }

            game_room_manager->ResizeRoom();
            game_room_manager->ResizeEditorRoom(editor_room);
        }

        if (JSONParser::audio::changed) {
            JSONParser::audio::ChangesApplied();
            try {
                audio_settings_menu->LoadConfiguration(
                    Strings::Menus::Main_Window::Paths::audio_settings_menu_config_path
                );
            } catch (HerionException::File::FileException& ex) {
                ex.UpdateStackTrace(GET_CONTEXT());
                throw;
            }
        }

        main_window->SetColor(COLORS::BLACK);
        main_window->Clear();

        CheckGameMode();

        main_window->Present();
        main_window->Sleep();
    }
}

void Engine::CheckGameMode() {
    Engine::GameState game_mode = GetGameState();

    switch (game_mode) {

    default:
        break;

    case Engine::GameState::MAIN_MENU:
        main_window->SetCurrentMenu(Strings::Menus::Main_Window::Names::main_menu_name);
        main_window->GetCurrentMenu()->Draw(main_window->GetRenderer());
        break;

    case Engine::GameState::GENERAL_SETTINGS_MENU:
        main_window->SetCurrentMenu(Strings::Menus::Main_Window::Names::general_settings_menu_name);
        main_window->GetCurrentMenu()->Draw(main_window->GetRenderer());
        break;

    case Engine::GameState::GRAPHICS_SETTINGS_MENU:
        main_window->SetCurrentMenu(Strings::Menus::Main_Window::Names::graphics_settings_menu_name);
        main_window->GetCurrentMenu()->Draw(main_window->GetRenderer());
        break;

    case Engine::GameState::AUDIO_SETTINGS_MENU:
        main_window->SetCurrentMenu(Strings::Menus::Main_Window::Names::audio_settings_menu_name);
        main_window->GetCurrentMenu()->Draw(main_window->GetRenderer());
        break;

    case Engine::GameState::PAUSE_MENU:
        main_window->SetCurrentMenu(Strings::Menus::Main_Window::Names::pause_menu_name);
        main_window->GetCurrentMenu()->Draw(main_window->GetRenderer());
        break;

    case Engine::GameState::EDITOR_MENU:
        main_window->SetCurrentMenu(Strings::Menus::Main_Window::Names::editor_menu_name);
        main_window->GetCurrentMenu()->Draw(main_window->GetRenderer());
        break;

    case Engine::GameState::LEVEL_EDITOR:
        editor_room->Draw(main_window->GetRenderer());

        if (editor_room->ShouldDrawAxis())
            editor_room->DrawAxis(main_window->GetRenderer());

        if (editor_room->ShouldDrawHitboxes())
            editor_room->DrawHitboxes(main_window->GetRenderer());

        for (const auto& [editor_win_name, editor_win] : editors_windows) {
            if (editor_win->IsOpen()) {
                editor_win->SetColor(COLORS::BLACK);
                editor_win->Clear();
                editor_win->GetCurrentMenu()->Draw(editor_win->GetRenderer());
                editor_win->Present();
                editor_win->Sleep();
            }
        }
        break;

    case Engine::GameState::ANIMATION_EDITOR:
        img_editor->DrawImage();
        break;

    case Engine::GameState::IN_GAME:
        game_room_manager->DrawCurrentRoom(main_window->GetRenderer());

        processor->update_player_movement(deltaTime);
        player->UpdateFrame();
        player->Draw();
        break;
    }
}

void Engine::SetGameState(GameState new_state) {
    Engine::previous_state = Engine::state;
    Engine::state = new_state;
}

Engine::GameState Engine::GetGameState() {
    return Engine::state;
}

Engine::GameState Engine::GetPreviousState() {
    return Engine::previous_state;
}