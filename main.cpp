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

    // Logger::EnableHTTPLogging();
    Logger::EnableFILELogging();
    Logger::EnableSTDOUTLogging();
    Logger::ClearTempLoggingFiles();

    /*
    auto& client = TcpClient::GetInstance();
    client.Init();
    client.ConnectAll( std::getenv("SERVER_IP") );
    */

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

    texture_manager.SetRenderer( window.GetRenderer() );
    texture_manager.LoadTextures("assets/all_textures.txt");

    room_manager.SetTextureManager( &texture_manager );
    room_manager.SetDimensions( window.GetWidth(), window.GetHeight(), 32, 18 );
    room_manager.GenerateRoom( room_manager.ICE, RoomManager::DIR_NONE ) ;

    main_menu.SetTextureManager( &texture_manager );
    main_menu.LoadCfg( "configs/menu/main_menu.cfg");
    main_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );

    settings_menu.SetTextureManager( &texture_manager );
    settings_menu.LoadCfg( "configs/menu/settings_menu.cfg" );
    settings_menu.SetDimension( (float)window.GetWidth(), (float)window.GetHeight() );

    pause_menu.SetTextureManager( &texture_manager );
    pause_menu.LoadCfg( "configs/menu/pause_menu.cfg" );
    pause_menu.SetDimension( (float)window.GetWidth(), (float)window.GetHeight() );

    processor.SetMenus("MAIN_MENU", &main_menu );
    processor.SetMenus("SETTINGS_MENU", &settings_menu );
    processor.SetMenus("PAUSE_MENU", &pause_menu );
    processor.SetPlayer( &player );
    processor.SetRoomManager( &room_manager );

    player.SetTextureManager( &texture_manager );

    player.LoadAnimation( "configs/animations/player/idle/idle_down.cfg", "IDLE_DOWN");
    player.LoadAnimation( "configs/animations/player/idle/idle_left.cfg", "IDLE_LEFT");
    player.LoadAnimation( "configs/animations/player/idle/idle_up.cfg", "IDLE_UP");
    player.LoadAnimation( "configs/animations/player/idle/idle_right.cfg", "IDLE_RIGHT");

    player.LoadAnimation( "configs/animations/player/run/run_down.cfg", "RUN_DOWN");
    player.LoadAnimation( "configs/animations/player/run/run_left.cfg", "RUN_LEFT");
    player.LoadAnimation( "configs/animations/player/run/run_up.cfg", "RUN_UP");
    player.LoadAnimation( "configs/animations/player/run/run_right.cfg", "RUN_RIGHT");

    SDL_Event event;

    while ( !processor.ShouldQuit() && player.GetGameMode() != Player::GameMode::EXIT ) {

        while ( SDL_PollEvent( &event ) ) {
            processor.SetEvent( event );
            processor.Process();
        }

        if ( JSONParser::graphics::Changed() ) {

            window.Resize();

            main_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );
            main_menu.LoadCfg( "configs/menu/main_menu.cfg" );

            settings_menu.SetDimension( static_cast<float>(window.GetWidth()), (float)window.GetHeight() );
            settings_menu.LoadCfg( "configs/menu/settings_menu.cfg" );

            pause_menu.SetDimension( static_cast<float>(window.GetWidth()), (float)window.GetHeight() );
            pause_menu.LoadCfg( "configs/menu/pause_menu.cfg" );

            room_manager.ResizeRoom();

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
                player.Update();
                player.Draw( window.GetRenderer() );
                break;

        }

        window.Present();
        window.Sleep();

    }


}

