//
// Created by david on 18/11/2025.
//

#ifndef HERION_HERO_ROOMMANAGER_HPP
#define HERION_HERO_ROOMMANAGER_HPP


#include <random>

#include "../../Textures/hpp/TextureManager.hpp"
#include "../../Exceptions//hpp/HerionFileException.hpp"
#include "Tile.hpp"
#include "Room.hpp"


class RoomManager {

private:
    TextureManager *textureManager;

    typedef struct Node{
        Room* room = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *up = nullptr;
        Node *down = nullptr;
    }Node;


    Node* spawn_room;
    Node* current_room;

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

    typedef enum {
        DIR_NONE,
        DIR_UP,
        DIR_LEFT,
        DIR_DOWN,
        DIR_RIGHT

    }Direction;

    RoomManager();

    ~RoomManager();

    void SetDimensions(int screen_width, int screen_height, int horizontal_tiles, int vertical_tiles);
    void SetTextureManager(TextureManager* texture_manager);
    void GenerateRoom( ROOM_TYPE room_type, Direction dir );
    [[nodiscard]] Room* GetCurrentRoom() const;

    void GoLeft();

    void GoRight();

    void GoUp();

    void GoDown();

    void ResizeRoom();

    void DrawCurrentRoom( SDL_Renderer* renderer) const;

};


#endif //HERION_HERO_ROOMMANAGER_HPP