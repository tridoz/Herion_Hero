
#ifndef HERION_HERO_TILE_HPP
#define HERION_HERO_TILE_HPP

#include <SDL3/SDL.h>

#include "../../Textures/hpp/Texture.hpp"
#include "../../Utils/hpp/Logger.hpp"
class Tile {
private:
    const Texture *texture;
    std::string code;
    bool isWalkable;
    SDL_FRect rect{};

public:

    Tile();
    ~Tile();

    /**
     * @brief Set the tile Texture
     * @param new_texture Texture to set
     */
    void SetTexture(const Texture *new_texture);

    /**
     * @brief Set the tile rect
     * @param x Coordinate x of the rect
     * @param y Coordinate y of the rect
     * @param w Width of the rect
     * @param h Height of the rect
     */
    void SetRect( float x, float y, float w, float h );

    /**
     * @brief Draw the tile
     * @param renderer Renderer needed to draw the tile
     */
    void Draw( SDL_Renderer* renderer ) const;

    /**
     * @brief Return the Tile rect
     * @return SDL_FRect*
     */
    SDL_FRect* GetRect();

    /**
     * @brief Return of the tile is walkable
     * @note Unesed
     * @return bool
     */
    [[nodiscard]] bool IsWalkable() const;

    void SetCode( std::string new_code );

};


#endif //HERION_HERO_TILE_HPP