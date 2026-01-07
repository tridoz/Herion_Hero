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
    int spawn_x, spawn_y;
public:
    Room();
    ~Room();

    std::vector< std::vector< Tile * > > GetTiles();

    void SetTiles(const std::vector< std::vector<Tile*> > &new_tiles);
    void Draw( SDL_Renderer* renderer );
    void SetSpawnCoord( int x, int y );
    int GetSpawnX() const;
    int GetSpawnY() const;

};

#endif //HERION_HERO_ROOM_HPP