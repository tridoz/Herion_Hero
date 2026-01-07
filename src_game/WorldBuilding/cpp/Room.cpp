//
// Created by david on 17/11/2025.
//

#include "../hpp/Room.hpp"

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


