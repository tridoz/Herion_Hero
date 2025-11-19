//
// Created by david on 17/11/2025.
//

#include "Room.hpp"

Room::Room() {}

Room::~Room() {

    for ( std::vector<Tile*> & tile_row : tiles) {
        tile_row.clear();
    }

    tiles.clear();

}

void Room::Draw(SDL_Renderer* renderer) {

    for ( std::vector<Tile*> & tiles_row : tiles) {
        for ( Tile* & tile : tiles_row) {
            tile->Draw(renderer);
        }
    }

}

void Room::SetTiles(std::vector<std::vector<Tile*>> tiles) {
    this->tiles = tiles;
    Logger::LogOK(
        std::time(nullptr),
        "SETTING",
        "Room",
        "SetTiles",
        "Tiles Setted Correctly"
        );
}


