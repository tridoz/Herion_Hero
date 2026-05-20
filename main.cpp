#include "src_game/UI/hpp/Window.hpp"
#include "src_game/Utils/hpp/Logger.hpp"
#include "src_game/Utils/hpp/InputProcessor.hpp"
#include "src_game/Textures/hpp/TextureManager.hpp"
#include "src_game/WorldBuilding/hpp/RoomManager.hpp"
#include "src_game/UI/hpp/Menu.hpp"
#include "src_game/Entities/hpp/Player.hpp"
#include "src_game/Utils/hpp/ButtonsFunctions.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>

#include "src_game/Exceptions/hpp/HerionFileException.hpp"
#include "src_game/UI/hpp/ButtonMenu.hpp"
#include "src_game/UI/hpp/ScrollPaneMenu.hpp"
#include "src_game/WorldBuilding/hpp/EditorRoom.hpp"


#ifdef _WIN32
    #include <stdlib.h>
#endif


int LoadEnv() {

    std::string base_path = "../";
    std::string path =  ".env";

    std::ifstream file(base_path + path);

    if ( !file.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "LOADING",
            "Main",
            "LoadEnv",
            " file: [" + path + "] " + strerror(errno)
            );
        return 0;
    }


    // Logger::LogOk(
    //     std::time(nullptr),
    //     "LOADING",
    //     "Main",
    //     "LoadEnv",
    //     ".env file loaded correctly"
    //     );

    std::string line;
    while ( std::getline(file, line) ) {
        if ( line.empty() || line[0] == '#' ) continue;

        size_t eqPos = line.find('=');

        if ( eqPos == std::string::npos ) continue;

        std::string key = line.substr(0, eqPos);
        std::string value = line.substr(eqPos + 1);

        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        #ifdef _WIN32
                _putenv_s(key.c_str(), value.c_str());
        #else
                setenv(key.c_str(), value.c_str(), 1);
        #endif
    }

    file.close();
    return 1;
}

int main ( int argc, char* argv[] ) {

    LoadEnv();

    //Logger::EnableHTTPLogging();

    Logger::EnableFILELogging();
    Logger::EnableSTDOUTLogging();
    Logger::ClearTempLoggingFiles();

    Window window(  "HERION HERO");

    std::unordered_map < std::string,  Window* > editors_windows = {
          { "TEXTURE_SELECTION", new Window("Texture selection", 500, 300) },
        { "ACTION_SELECTION", new Window("Action selection", 500, 300) }
    };

    InputProcessor processor;

    TextureManager main_texture_manager;
    TextureManager texture_selection_texture_manager;
    TextureManager action_selection_texture_manager;

    RoomManager game_room_manager;

    EditorRoom editor_room;

    Player player;

    ButtonMenu main_menu;
    ButtonMenu settings_menu;
    ButtonMenu pause_menu;
    ButtonMenu editor_menu;

    ScrollPaneMenu texture_selection_menu;

    ButtonMenu action_selection_menu;

    Player::PlayerState player_state;
    Player::GameMode game_mode;

    ButtonsFunctions::SetPlayer( &player );

    window.SetMenu( "MAIN_MENU", &main_menu );
    window.SetMenu( "SETTINGS_MENU", &settings_menu );
    window.SetMenu( "PAUSE_MENU", &pause_menu );
    window.SetMenu( "EDITOR_MENU", &editor_menu );

    editors_windows.at("TEXTURE_SELECTION")->SetMenu("TEXTURE_SELECTION", &texture_selection_menu );
    editors_windows.at("TEXTURE_SELECTION")->SetCurrentMenu("TEXTURE_SELECTION");

    editors_windows.at("ACTION_SELECTION")->SetMenu("ACTION_SELECTION", &action_selection_menu );
    editors_windows.at("ACTION_SELECTION")->SetCurrentMenu("ACTION_SELECTION");

    window.LoadCursors( "Assets/all_cursors.txt");

    main_texture_manager.SetRenderer( window.GetRenderer() );
    texture_selection_texture_manager.SetRenderer( editors_windows.at("TEXTURE_SELECTION")->GetRenderer() );
    action_selection_texture_manager.SetRenderer( editors_windows.at("ACTION_SELECTION")->GetRenderer() );

    try {

        main_texture_manager.LoadTextures("Assets/all_textures.txt");
        texture_selection_texture_manager.LoadTextures("Assets/all_textures.txt");
        action_selection_texture_manager.LoadTextures("Assets/all_textures.txt");

    } catch ( HerionException::File::FileException &ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        Logger::LogStackTrace( std::time(nullptr), ex.GetStackTrace() );
        return -1;
    }

    game_room_manager.SetTextureManager( &main_texture_manager );
    game_room_manager.SetDimensions( window.GetWidth(), window.GetHeight(), 32, 18 );

    try {
        game_room_manager.GenerateRoom( RoomManager::DIRECTION::DIR_NONE, "../maps/room1/base_plane_textures.hhmap") ;
    } catch ( HerionException::File::FileException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        Logger::LogStackTrace( std::time(nullptr), ex.GetStackTrace() );
        return -1;
    }

    main_menu.SetTextureManager( &main_texture_manager );
    main_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );

    settings_menu.SetTextureManager( &main_texture_manager );
    settings_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );

    pause_menu.SetTextureManager( &main_texture_manager );
    pause_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );

    editor_menu.SetTextureManager( &main_texture_manager );
    editor_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );

    texture_selection_menu.SetTextureManager( &texture_selection_texture_manager );
    texture_selection_menu.SetDimension( static_cast<float>( editors_windows.at("TEXTURE_SELECTION")->GetWidth()), static_cast<float>(editors_windows.at("TEXTURE_SELECTION")->GetHeight()) );

    action_selection_menu.SetTextureManager( &action_selection_texture_manager );
    action_selection_menu.SetDimension( static_cast<float>( editors_windows.at("ACTION_SELECTION")->GetWidth() ) , static_cast<float>(editors_windows.at("ACTION_SELECTION")->GetHeight() ) );

    try {

        main_menu.LoadConfiguration( "configs/menus/main_window/main_menu.json");
        settings_menu.LoadConfiguration( "configs/menus/main_window/settings_menu.json" );
        pause_menu.LoadConfiguration( "configs/menus/main_window/pause_menu.json" );
        editor_menu.LoadConfiguration( "configs/menus/main_window/editor_menu.json" );

        texture_selection_menu.LoadConfiguration("configs/menus/level_editors_windows/directory_texture_selection.json");
        action_selection_menu.LoadConfiguration("configs/menus/level_editors_windows/action_selection.json");

    } catch ( HerionException::File::FileException &ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        Logger::LogStackTrace( std::time(nullptr), ex.GetStackTrace() );
        return -1;
    }

    processor.SetMenus("MAIN_MENU", &main_menu );
    processor.SetMenus("SETTINGS_MENU", &settings_menu );
    processor.SetMenus("PAUSE_MENU", &pause_menu );
    processor.SetMenus("EDITOR_MENU", &editor_menu );
    processor.SetMenus("TEXTURE_SELECTIONS", &texture_selection_menu );
    processor.SetMenus("ACTION_SELECTION", &action_selection_menu );

    processor.SetTextureManager("MAIN", &main_texture_manager );
    processor.SetTextureManager("EDITOR", &texture_selection_texture_manager);
    processor.SetTextureManager("ACTION", &action_selection_texture_manager);

    processor.SetEditorRoom( &editor_room );

    processor.SetWindowTools( editors_windows );

    processor.SetPlayer( &player );
    processor.SetRoomManager( &game_room_manager );

    player.Spawn( game_room_manager.GetPlayerSpawnCellX() , game_room_manager.GetPlayerSpawnCellY()  );
    player.SetTextureManager( &main_texture_manager );

    try {
        player.LoadAnimation( "configs/animations/player.json");
    } catch ( HerionException::File::FileException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        Logger::LogStackTrace( std::time(nullptr), ex.GetStackTrace() );
        return -1;
    }

    SDL_Event event;

    Uint32 last_frame_time = SDL_GetTicks();

    game_room_manager.GenerateEditorRoom( &editor_room, "../maps/room1/base_plane_textures.hhmap" );

    while ( !processor.ShouldQuit() && player.GetGameMode() != Player::GameMode::EXIT ) {

        Uint32 current_time = SDL_GetTicks();
        float deltaTime = (current_time - last_frame_time) / 1000.0f;
        last_frame_time = current_time;

        while ( SDL_PollEvent( &event ) ) {
            processor.SetEvent( event );
            processor.Process();
        }

        if ( JSONParser::graphics::Changed() ) {
            window.Resize();

            main_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );
            settings_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );
            pause_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );
            editor_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );

            try {
                main_menu.LoadConfiguration( "configs/menus/main_window/main_menu.json");
                settings_menu.LoadConfiguration( "configs/menus/main_window/settings_menu.json" );
                pause_menu.LoadConfiguration( "configs/menus/main_window/pause_menu.json" );
                editor_menu.LoadConfiguration( "configs/menus/main_window/editor_menu.json" );
            } catch ( HerionException::File::FileException &ex ) {
                ex.UpdateStackTrace( GET_CONTEXT() );
                Logger::LogStackTrace( std::time(nullptr), ex.GetStackTrace() );
                return -1;
            }

            game_room_manager.ResizeRoom();
            game_room_manager.ResizeEditorRoom( &editor_room );

            player.Resize();

        }

        window.SetColor( COLORS::BLACK );
        window.Clear();

        game_mode = player.GetGameMode();

        switch ( game_mode ) {

            default:
                break;

            case Player::GameMode::MAIN_MENU:
                window.SetCurrentMenu("MAIN_MENU");
                window.GetCurrentMenu()->Draw( window.GetRenderer() );
                break;

            case Player::GameMode::SETTINGS_MENU:
                window.SetCurrentMenu("SETTINGS_MENU");
                window.GetCurrentMenu()->Draw( window.GetRenderer() );
                break;

            case Player::GameMode::PAUSE_MENU:
                window.SetCurrentMenu("PAUSE_MENU");
                window.GetCurrentMenu()->Draw( window.GetRenderer() );
                break;

            case Player::GameMode::EDITOR_MENU:
                window.SetCurrentMenu("EDITOR_MENU");
                window.GetCurrentMenu()->Draw( window.GetRenderer() );
                break;

            case Player::GameMode::LEVEL_EDITOR:
                editor_room.Draw( window.GetRenderer() );
                if ( editor_room.ShouldDrawAxis() ) {
                    editor_room.DrawAxis( window.GetRenderer() );
                }

                for ( const auto [editor_win_name, editor_win] : editors_windows ) {
                    if ( editor_win->IsOpen() ) {
                        editor_win->SetColor( COLORS::BLACK );
                        editor_win->Clear();
                        editor_win->GetCurrentMenu()->Draw(editor_win->GetRenderer());
                        editor_win->Present();
                        editor_win->Sleep();
                    }
                }

                break;

            case Player::GameMode::IN_GAME:
                game_room_manager.DrawCurrentRoom( window.GetRenderer() );
                player.Update();

                processor.update_player_movement( deltaTime );
                player.Draw( window.GetRenderer() );
                break;

        }

        window.Present();
        window.Sleep();

    }

}

