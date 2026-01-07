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

    InputProcessor processor;

    TextureManager texture_manager;

    RoomManager room_manager;

    Player player;

    Menu main_menu;
    Menu settings_menu;
    Menu pause_menu;

    Player::PlayerState player_state;
    Player::GameMode game_mode;

    ButtonsFunctions::SetPlayer( &player );

    window.LoadCursors( "assets/all_cursors.txt");

    texture_manager.SetRenderer( window.GetRenderer() );

    try {
        texture_manager.LoadTextures("assets/all_textures.txt");
    } catch ( HerionException::File::FileException &ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        Logger::LogStackTrace( std::time(nullptr), ex.GetStackTrace() );
        return -1;
    }

    room_manager.SetTextureManager( &texture_manager );
    room_manager.SetDimensions( window.GetWidth(), window.GetHeight(), 32, 18 );

    try {
        room_manager.GenerateRoom( RoomManager::DIR_NONE) ;
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

    try {
        main_menu.LoadCfg( "configs/menu/main_menu.json");
        settings_menu.LoadCfg( "configs/menu/settings_menu.json" );
        pause_menu.LoadCfg( "configs/menu/pause_menu.json" );
    } catch ( HerionException::File::FileException &ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        Logger::LogStackTrace( std::time(nullptr), ex.GetStackTrace() );
        return -1;
    }

    processor.SetMenus("MAIN_MENU", &main_menu );
    processor.SetMenus("SETTINGS_MENU", &settings_menu );
    processor.SetMenus("PAUSE_MENU", &pause_menu );
    processor.SetPlayer( &player );
    processor.SetRoomManager( &room_manager );

    player.Spawn( room_manager.GetPlayerSpawnCellX() , room_manager.GetPlayerSpawnCellY()  );
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
            settings_menu.SetDimension( static_cast<float>(window.GetWidth()), (float)window.GetHeight() );
            pause_menu.SetDimension( static_cast<float>(window.GetWidth()), (float)window.GetHeight() );

            try {
                main_menu.LoadCfg( "configs/menu/main_menu.json");
                settings_menu.LoadCfg( "configs/menu/settings_menu.json" );
                pause_menu.LoadCfg( "configs/menu/pause_menu.json" );
            } catch ( HerionException::File::FileException &ex ) {
                ex.UpdateStackTrace( GET_CONTEXT() );
                Logger::LogStackTrace( std::time(nullptr), ex.GetStackTrace() );
                return -1;
            }

            room_manager.ResizeRoom();
            player.Resize();
        }

        window.SetColor( COLORS::BLACK );
        window.Clear();

        game_mode = player.GetGameMode();

        switch ( game_mode ) {

            default:
                break;

            case Player::GameMode::MAIN_MENU:
                main_menu.Draw( window.GetRenderer() );
                break;

            case Player::GameMode::SETTINGS_MENU:
                settings_menu.Draw( window.GetRenderer() );
                break;

            case Player::GameMode::PAUSE_MENU:
                pause_menu.Draw( window.GetRenderer() );
                break;

            case Player::GameMode::IN_GAME:
                room_manager.DrawCurrentRoom( window.GetRenderer() );
                player.Update( window.GetRenderer() );

                processor.update_player_movement( deltaTime );
                player.Draw( window.GetRenderer() );
                break;

        }

        window.Present();
        window.Sleep();

    }

}

