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
    int player_spawn_cell_y;
    int player_spawn_cell_x;

    /**
     * @struct Node
     * @brief Struct to a multidirectional linked list to resemble a "map"
     */
    struct Node{
        Room* room = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *up = nullptr;
        Node *down = nullptr;
    };


    Node* spawn_room;
    Node* current_room;

    int screen_width;
    int screen_height;
    int horizontal_tiles;
    int vertical_tiles;

public:
    /**
     * @enum ROOM_TYPE
     * @brief All ROOM_TYPE so the engine knows which texture need to be rendered
     */
    enum class ROOM_TYPE{
        ANCIENT_RUINS,
        LAVA,
        ICE,
        DARK,
        HOLY,
        POISON
    };

    /**
     * @enum DIRECTION
     * @brief All direction to create a new room in a certain directon
     */
    enum class DIRECTION{
        DIR_NONE,
        DIR_UP,
        DIR_LEFT,
        DIR_DOWN,
        DIR_RIGHT
    };

    RoomManager();

    ~RoomManager();

    /**
     * @brief Set the dimensions of the room and the single tiles.
     * @param screen_width Width of the screen
     * @param screen_height Height of the screen
     * @param horizontal_tiles How many tiles is the screen divided in horizontally
     * @param vertical_tiles How many tiles is the screen divided in vertically
     */
    void SetDimensions(int screen_width, int screen_height, int horizontal_tiles, int vertical_tiles);

    /**
     * @brief Set the TextureManager to get the texture while generating the room
     * @param texture_manager
     */
    void SetTextureManager(TextureManager* texture_manager);

    /**
     * @brief Generate a room in a given direction
     * @param dir Direction in which the room needs to be generated
     * @param map_path Path of the map file used to generate the room
     */
    void GenerateRoom(DIRECTION dir, const std::string& map_path );

    /**
     * @brief Generated the room for the Level Editor
     * @param room Pointer to the Level Editor room
     * @param map_path Path to the map_file of the Level Editor room
     */
    void GenerateEditorRoom(Room* room, const std::string& map_path );

    /**
     * @brief Resize the current room
     */
    void ResizeRoom();

    /**
     * @brief Resize the Level Editor room
     * @param room Pointer to the Level Editor room that needs to be resized
     */
    void ResizeEditorRoom( Room* room );

    /**
     * @brief Return a pointer to the current room
     * @return Room*
     */
    [[nodiscard]] Room* GetCurrentRoom() const;

    /**
     * @brief Generate a room in the left direction if not present and set to current_room to it
     */
    void GoLeft();

    /**
     * @brief Generate a room in the right direction if not present and set to current_room to it
     */
    void GoRight();

    /**
     * @brief Generate a room in the up direction if not present and set to current_room to it
     */
    void GoUp();

    /**
     * @brief Generate a room in the down direction if not present and set to current_room to it
     */
    void GoDown();

    /**
     * @brief Return the Y cell cordinate in which the player spawn
     * @return int
     */
    int GetPlayerSpawnCellY() const;

    /**
     * @brief Return the X cell cordinate in which the player spawn
     * @return int
     */
    int GetPlayerSpawnCellX() const;

    /**
     * @brief Draw the current room
     * @param renderer Renderer in which the room will be drawn
     */
    void DrawCurrentRoom( SDL_Renderer* renderer) const;

};


#endif //HERION_HERO_ROOMMANAGER_HPP