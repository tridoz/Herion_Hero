//
// Created by david on 17/11/2025.
//

#include "../hpp/Room.hpp"

#include "../../Utils/hpp/JSONParser.hpp"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_rect.h"

Room::Room() {
}

Room::~Room() {

    for (std::vector<Tile*>& tile_row : tiles) {
        for (const Tile* tile : tile_row) {
            delete tile;
        }
    }

    tiles.clear();
}

std::vector<std::vector<Tile*>> Room::GetTiles() {
    return this->tiles;
}

void Room::Draw(SDL_Renderer* renderer) {

    for (std::vector<Tile*>& tiles_row : tiles) {
        for (Tile*& tile : tiles_row) {
            tile->Draw(renderer);
        }
    }
}

void Room::SetTiles(const std::vector<std::vector<Tile*>>& new_tiles) {
    this->tiles = new_tiles;
    this->horizontal_tiles = this->tiles[0].size();
    this->vertical_tiles = this->tiles.size();

    this->tile_width = width / horizontal_tiles;
    this->tile_height = height / vertical_tiles;
}

void Room::SetSpawnCoord(int x, int y) {
    this->spawn_x = x;
    this->spawn_y = y;
}

int Room::GetSpawnX() const {
    return spawn_x;
}

int Room::GetSpawnY() const {
    return spawn_y;
}

int Room::GetHorizontalTiles() {
    return horizontal_tiles;
}

int Room::GetVerticalTiles() {
    return vertical_tiles;
}

void Room::SetFilepath(const std::string& filepath) {
    this->filepath = filepath;
}

void Room::CheckPlayerCollision(Player* player) {
}
