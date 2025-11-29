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

public:
    Room();
    ~Room();

    std::vector< std::vector< Tile * > > GetTiles();

    void SetTiles(std::vector< std::vector<Tile*> > tiles);
    void Draw( SDL_Renderer* renderer );

};

#endif //HERION_HERO_ROOM_HPP