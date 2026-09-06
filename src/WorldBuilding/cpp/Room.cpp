//
// Created by david on 17/11/2025.
//

#include "../hpp/Room.hpp"

#include "../../Utils/hpp/JSONParser.hpp"
#include "Player.hpp"
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

auto Room::GetTiles() -> std::vector<std::vector<Tile*>> {
    return this->tiles;
}

auto Room::Draw(SDL_Renderer* renderer) -> void {

    for (std::vector<Tile*>& tiles_row : tiles) {
        for (Tile*& tile : tiles_row) {
            tile->Draw(renderer);
        }
    }
}

auto Room::SetTiles(const std::vector<std::vector<Tile*>>& new_tiles) -> void {
    this->tiles = new_tiles;
    this->horizontal_tiles = static_cast<int>(this->tiles[0].size());
    this->vertical_tiles = static_cast<int>(this->tiles.size());

    this->tile_width = static_cast<float>(width) / static_cast<float>(horizontal_tiles);
    this->tile_height = static_cast<float>(height) / static_cast<float>(vertical_tiles);
}

auto Room::SetSpawnCoord(int x, int y) -> void {
    this->spawn_x = x;
    this->spawn_y = y;
}

auto Room::GetSpawnX() const -> int {
    return spawn_x;
}

auto Room::GetSpawnY() const -> int {
    return spawn_y;
}

auto Room::GetHorizontalTiles() const -> int {
    return horizontal_tiles;
}

auto Room::GetVerticalTiles() const -> int {
    return vertical_tiles;
}

auto Room::SetFilepath(const std::string& filepath) -> void {
    this->filepath = filepath;
}

auto Room::CheckPlayerCollision(Player* player) -> void {
    auto sprite = player->GetComponent<ECS::Components::Sprites>();
    for (auto& row : tiles) {
        for (Tile* tile : row) {
            if (!tile->HasHitbox())
                continue;

            SDL_FRect* rect = tile->GetRect();

            SDL_HasRectIntersectionFloat(rect, sprite->sprite_rect.to_sdl());
        }
    }
}
