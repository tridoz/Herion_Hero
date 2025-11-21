
#ifndef HERION_HERO_TILE_HPP
#define HERION_HERO_TILE_HPP

#include <SDL3/SDL.h>

#include "Texture.hpp"
#include "Logger.hpp"
class Tile {
private:
    Texture texture;
    bool isWalkable;
    SDL_FRect rect{};

public:

    Tile();
    ~Tile();

    void SetTexture( const Texture& texture );
    void SetRect( float x, float y, float w, float h );
    void Draw( SDL_Renderer* renderer ) const;
    SDL_FRect* GetRect();

    [[nodiscard]] bool IsWalkable() const;

};


#endif //HERION_HERO_TILE_HPP