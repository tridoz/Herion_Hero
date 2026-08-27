//
// Created by david on 18/11/2025.
//

#ifndef HERION_HERO_ROOMMANAGER_HPP
#define HERION_HERO_ROOMMANAGER_HPP

#include "../../Exceptions//hpp/HerionFileException.hpp"
#include "../../Textures/hpp/TextureManager.hpp"
#include "EditorRoom.hpp"
#include "Room.hpp"
#include "Tile.hpp"

class RoomManager {

  private:
    TextureManager* textureManager;
    int player_spawn_cell_y;
    int player_spawn_cell_x;

    struct Node {
        Room* room = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* up = nullptr;
        Node* down = nullptr;
    };

    Node* spawn_room;
    Node* current_room;

    int screen_width;
    int screen_height;
    int horizontal_tiles;
    int vertical_tiles;

  public:
    enum class ROOM_TYPE : std::uint8_t { ANCIENT_RUINS, LAVA, ICE, DARK, HOLY, POISON };

    enum class DIRECTION : std::uint8_t { DIR_NONE, DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT };

    RoomManager();

    ~RoomManager();

    [[nodiscard]] auto SetDimensions(int, int, int, int) -> void;
    auto SetTextureManager(TextureManager*) -> void;
    auto GenerateRoom(DIRECTION, const std::string&) -> void;
    auto GenerateEditorRoom(EditorRoom*, const std::string&) -> void;
    auto ResizeRoom() -> void;
    auto ResizeEditorRoom(Room*) -> void;
    [[nodiscard]] auto GetCurrentRoom() const -> Room*;
    auto GoLeft() -> void;
    auto GoRight() -> void;
    auto GoUp() -> void;
    auto GoDown() -> void;
    [[nodiscard]] auto GetPlayerSpawnCellY() const -> int;
    [[nodiscard]] auto GetPlayerSpawnCellX() const -> int;
    auto DrawCurrentRoom(SDL_Renderer*) const -> void;
};

#endif // HERION_HERO_ROOMMANAGER_HPP
