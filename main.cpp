#include "src/Window.hpp"
#include "src/Logger.hpp"
#include "src/InputProcessor.hpp"
#include "src/TextureManager.hpp"
#include "src/RoomManager.hpp"


int main ( int argc, char* argv[] ) {

    const Window window(1920, 1080, "HERION HERO");

    InputProcessor processor;
    TextureManager texture_manager;

    texture_manager.SetRenderer( window.GetRenderer() );
    texture_manager.LoadTextures("assets/all_textures.txt");

    RoomManager room_manager;

    room_manager.SetTextureManager( &texture_manager );
    room_manager.SetDimensions( 1920, 1080, 32, 18 );
    room_manager.GenerateSpawnRoom( room_manager.ICE ) ;

    SDL_Event event;

    while ( !processor.ShouldQuit() ) {

        while ( SDL_PollEvent( &event ) ) {

            SDL_SetRenderDrawColor( window.GetRenderer(), 0, 0, 0, 255 ) ;
            SDL_RenderClear( window.GetRenderer() );

            processor.SetEvent( event );
            processor.Process();

            room_manager.DrawCurrentRoom( window.GetRenderer() );

            SDL_RenderPresent( window.GetRenderer() );

        }

    }

}

