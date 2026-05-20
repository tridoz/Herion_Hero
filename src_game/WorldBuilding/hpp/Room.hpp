//
// Created by david on 17/11/2025.
//

#ifndef HERION_HERO_ROOM_HPP
#define HERION_HERO_ROOM_HPP

#include <vector>

#include "Tile.hpp"


class Room {

private:
    std::vector< std::vector<Tile* > > tiles;
    Texture* current_editor_texture;

    int horizontal_tiles, vertical_tiles;
    int spawn_x, spawn_y;
public:
    Room();
    ~Room();

    /**
     * @brief Return the tiles
     * @return std::vector < std::vector < Tile* > >
     */
    std::vector< std::vector< Tile * > > GetTiles();

    /**
     * @brief Set the tiles to draw after generating them in RoomManager::GenerateRoom
     * @param new_tiles The tiles to set
     */
    void SetTiles(const std::vector< std::vector<Tile*> > &new_tiles);

    /**
     * @brief Draw the room
     * @param renderer Renderer needed to draw the rrom
     */
    void Draw( SDL_Renderer* renderer );

    /**
     * @brief Draw the axis for each tile (used only in Level Editor mode)
     * @param renderer Renderer needed to draw the axis
     */
    void DrawAxis( SDL_Renderer* renderer ) const;

    /**
     * @brief Set the spawn coordinates of the room
     * @param x Coordinate X of spawn
     * @param y Coordinate Y of spawn
     */
    void SetSpawnCoord( int x, int y );

    /**
     * @brief Return the X spawn coordinate
     * @return int
     */
    int GetSpawnX() const;

    /**
     * @brief Return the Y spawn coordinate
     * @return int
     */
    int GetSpawnY() const;

    void SetCurrentEditorTexture( Texture* texture );
    Texture* GetCurrentEditorTexture();

    void ModifyOneTile( Texture* txt, int col, int row );

    int GetHorizontalTiles();
    int GetVerticalTiles();

};

#endif //HERION_HERO_ROOM_HPP