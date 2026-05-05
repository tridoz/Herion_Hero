//
// Created by david on 17/11/2025.
//

#include "../hpp/Room.hpp"

#include "../../Utils/hpp/JSONParser.hpp"

Room::Room() {}

Room::~Room() {

    for ( std::vector<Tile*> & tile_row : tiles) {
        for (const Tile* tile : tile_row) {
            delete tile;
        }
    }

    tiles.clear();

}

std::vector< std::vector<Tile* > > Room::GetTiles() {
    return this->tiles;
}

void Room::Draw(SDL_Renderer* renderer) {

    for ( std::vector<Tile*> & tiles_row : tiles) {
        for ( Tile* & tile : tiles_row) {
            tile->Draw(renderer);
        }
    }

}

void Room::DrawAxis(SDL_Renderer* renderer) const {

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

    const int width = JSONParser::graphics::GetWidth();
    const int height = JSONParser::graphics::GetHeight();

    const int horizontal_tiles = tiles[0].size();
    const int vertical_tiles = tiles.size();

    const float tile_width = width / horizontal_tiles;
    const float tile_height = height / vertical_tiles;

    for ( int i = 0 ; i < horizontal_tiles ; ++i ) {
        SDL_RenderLine( renderer, i*tile_width, 0, i*tile_width, height );
    }

    for ( int i = 0 ; i < vertical_tiles ; ++i ) {
        SDL_RenderLine( renderer, 0, i*tile_height, i*width, i*tile_height );
    }

}

void Room::SetTiles(const std::vector<std::vector<Tile*>> &new_tiles) {
    this->tiles = new_tiles;
}

void Room::SetSpawnCoord(int x, int y) {
    this -> spawn_x = x;
    this -> spawn_y = y;
}

int Room::GetSpawnX() const {
    return spawn_x;
}

int Room::GetSpawnY() const {
    return spawn_y;
}


