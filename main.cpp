#include "src_game/Window.hpp"
#include "src_game/Logger.hpp"
#include "src_game/InputProcessor.hpp"
#include "src_game/TextureManager.hpp"
#include "src_game/RoomManager.hpp"
#include "src_game/Menu.hpp"
#include "src_game/Player.hpp"
#include "src_game/ButtonsFunctions.hpp"

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

    Logger::LogOK(
        std::time(nullptr),
        "LOADING",
        "Main",
        "LoadEnv",
        ".env file loaded correctly"
        );

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

    const Window window(  "HERION HERO");

    InputProcessor processor;

    TextureManager texture_manager;

    RoomManager room_manager;

    Player player;

    Menu main_menu;
    Menu settings_menu;

    Player::PlayerState player_state;
    Player::GameMode game_mode;

    ButtonsFunctions::SetPlayer( &player );

    texture_manager.SetRenderer( window.GetRenderer() );
    texture_manager.LoadTextures("assets/all_textures.txt");

    room_manager.SetTextureManager( &texture_manager );
    room_manager.SetDimensions( window.GetWidth(), window.GetHeight(), 32, 18 );
    room_manager.GenerateSpawnRoom( room_manager.ICE ) ;

    main_menu.SetTextureManager( &texture_manager );
    main_menu.LoadCfg( "configs/menu/main_menu.cfg");
    main_menu.SetDimension( static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) );

    settings_menu.SetTextureManager( &texture_manager );
    settings_menu.LoadCfg( "configs/menu/settings_menu.cfg" );
    settings_menu.SetDimension( (float)window.GetWidth(), (float)window.GetHeight() );

    processor.SetMenus("MAIN_MENU", &main_menu );
    processor.SetMenus("SETTINGS_MENU", &settings_menu );
    processor.SetPlayer( &player );

    SDL_Event event;

    while ( !processor.ShouldQuit() && player.GetGameMode() != Player::EXIT ) {

        while ( SDL_PollEvent( &event ) ) {
            processor.SetEvent( event );
            processor.Process();
        }

        window.SetColor( COLORS::BLACK );
        window.Clear();

        game_mode = player.GetGameMode();

        switch ( game_mode ) {

            default:
                break;

            case Player::MAIN_MENU:
                main_menu.Draw( window.GetRenderer() );
                break;

            case Player::SETTINGS_MENU:
                settings_menu.Draw( window.GetRenderer() );
                break;

            case Player::IN_GAME:
                room_manager.DrawCurrentRoom( window.GetRenderer() );
                break;

        }

        window.Present();

    }

}

