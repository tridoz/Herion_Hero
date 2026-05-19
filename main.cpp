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

    TextureManager texture_manager;

    RoomManager game_room_manager;
    Room editor_room;

    Player player;

    Menu main_menu;
    Menu settings_menu;
    Menu pause_menu;
    Menu editor_menu;

    Menu texture_selection_menu;

    Player::PlayerState player_state;
    Player::GameMode game_mode;

    ButtonsFunctions::SetPlayer( &player );

    window.SetMenu( "MAIN_MENU", &main_menu );
    window.SetMenu( "SETTINGS_MENU", &settings_menu );
    window.SetMenu( "PAUSE_MENU", &pause_menu );
    window.SetMenu( "EDITOR_MENU", &editor_menu );
    window.SetMenu( "TEXTURE_SELECTIONS", &texture_selection_menu );

    window.LoadCursors( "Assets/all_cursors.txt");

    texture_manager.SetRenderer( window.GetRenderer() );

    try {
        texture_manager.LoadTextures("Assets/all_textures.txt");
    } catch ( HerionException::File::FileException &ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        Logger::LogStackTrace( std::time(nullptr), ex.GetStackTrace() );
        return -1;
    }

    game_room_manager.SetTextureManager( &texture_manager );
    game_room_manager.SetDimensions( window.GetWidth(), window.GetHeight(), 32, 18 );

    try {
        game_room_manager.GenerateRoom( RoomManager::DIRECTION::DIR_NONE) ;
    } catch ( HerionException::File::FileException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        Logger::LogStackTrace( std::time(nullptr), ex.GetStackTrace() );
        return -1;
    }

    main_menu.SetTextureManager( &texture_manager );
    main_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );

    settings_menu.SetTextureManager( &texture_manager );
    settings_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );

    pause_menu.SetTextureManager( &texture_manager );
    pause_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );

    editor_menu.SetTextureManager( &texture_manager );
    editor_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );

    texture_selection_menu.SetTextureManager( &texture_manager );
    texture_selection_menu.SetDimension( static_cast<float>( editors_windows.at("TEXTURE_SELECTION")->GetWidth()), static_cast<float>(editors_windows.at("TEXTURE_SELECTION")->GetHeight()) );

    try {
        main_menu.LoadCfg( "configs/menus/main_window/main_menu.json");
        settings_menu.LoadCfg( "configs/menus/main_window/settings_menu.json" );
        pause_menu.LoadCfg( "configs/menus/main_window/pause_menu.json" );
        editor_menu.LoadCfg( "configs/menus/main_window/editor_menu.json" );

        texture_selection_menu.LoadCfg("configs/menus/level_editors_windows/directory_texture_selection.json");

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

    processor.SetWindowTools( editors_windows );

    processor.SetPlayer( &player );
    processor.SetRoomManager( &game_room_manager );

    player.Spawn( game_room_manager.GetPlayerSpawnCellX() , game_room_manager.GetPlayerSpawnCellY()  );
    player.SetTextureManager( &texture_manager );

    try {
        player.LoadAnimation( "configs/animations/player.json");
    } catch ( HerionException::File::FileException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        Logger::LogStackTrace( std::time(nullptr), ex.GetStackTrace() );
        return -1;
    }

    SDL_Event event;

    Uint32 last_frame_time = SDL_GetTicks();
    bool running = true;

    game_room_manager.GenerateEditorRoom( &editor_room, "../maps/room1/map.hhmap" );

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
                main_menu.LoadCfg( "configs/menus/main_window/main_menu.json");
                settings_menu.LoadCfg( "configs/menus/main_window/settings_menu.json" );
                pause_menu.LoadCfg( "configs/menus/main_window/pause_menu.json" );
                editor_menu.LoadCfg( "configs/menus/main_window/editor_menu.json" );
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
                window.GetMenu("MAIN_MENU")->Draw( window.GetRenderer() );
                break;

            case Player::GameMode::SETTINGS_MENU:
                window.GetMenu("SETTINGS_MENU")->Draw( window.GetRenderer() );
                break;

            case Player::GameMode::PAUSE_MENU:
                window.GetMenu("PAUSE_MENU")->Draw( window.GetRenderer() );
                break;

            case Player::GameMode::EDITOR_MENU:
                window.GetMenu("EDITOR_MENU")->Draw( window.GetRenderer() );
                break;

            case Player::GameMode::TEXTURE_SELECTION:
                window.GetMenu("TEXTURE_SELECTIONS")->Draw( window.GetRenderer() );
                break;

            case Player::GameMode::LEVEL_EDITOR:
                editor_room.Draw( window.GetRenderer() );
                editor_room.DrawAxis( window.GetRenderer() );


                for ( const auto [editor_win_name, editor_win] : editors_windows ) {
                    if ( editor_win->IsOpen() ) {
                        editor_win->Clear();
                        editor_win->GetMenu("")->Draw(editor_win->GetRenderer());
                        editor_win->Present();
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

