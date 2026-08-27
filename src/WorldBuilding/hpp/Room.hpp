//
// Created by david on 17/11/2025.
//

#ifndef HERION_HERO_ROOM_HPP
#define HERION_HERO_ROOM_HPP

#include <vector>

#include "../../Entities/hpp/Player.hpp"
#include "Tile.hpp"

class Room {

  protected:
    std::vector<std::vector<Tile*>> tiles;

    std::string filepath;

    int horizontal_tiles, vertical_tiles;
    int width, height;
    float tile_width, tile_height;
    int spawn_x, spawn_y;

  public:
    Room();
    ~Room();

    auto GetTiles() -> std::vector<std::vector<Tile*>>;
    auto SetTiles(const std::vector<std::vector<Tile*>>&) -> void;
    auto Draw(SDL_Renderer*) -> void;
    auto SetSpawnCoord(int, int) -> void;
    [[nodiscard]] auto GetSpawnX() const -> int;
    [[nodiscard]] auto GetSpawnY() const -> int;
    [[nodiscard]] auto GetHorizontalTiles() const -> int;
    [[nodiscard]] auto GetVerticalTiles() const -> int;
    auto SetFilepath(const std::string&) -> void;
    auto CheckPlayerCollision(Player*) -> void;
};

#endif // HERION_HERO_ROOM_HPP
