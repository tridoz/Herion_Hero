//
// Created by david on 18/11/2025.
//

#ifndef HERION_HERO_ROOMMANAGER_HPP
#define HERION_HERO_ROOMMANAGER_HPP


#include <random>

#include "../Textures/TextureManager.hpp"
#include "Tile.hpp"
#include "Room.hpp"


class RoomManager {

private:
    TextureManager *textureManager;

    typedef struct Node{
        Room* room;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *up = nullptr;
        Node *down = nullptr;
    }Node;

    Node* spawn_room;
    Node* CurrentRoom;

    int screen_width;
    int screen_height;
    int horizontal_tiles;
    int vertical_tiles;

public:

    typedef enum {
        ANCIENT_RUINS,
        LAVA,
        ICE,
        DARK,
        HOLY,
        POISON
    }ROOM_TYPE;

    RoomManager();

    void SetDimensions(int screen_width, int screen_height, int horizontal_tiles, int vertical_tiles);
    void SetTextureManager(TextureManager* texture_manager);
    void GenerateSpawnRoom( ROOM_TYPE room_type);
    void DrawCurrentRoom( SDL_Renderer* renderer) const;

};


#endif //HERION_HERO_ROOMMANAGER_HPP