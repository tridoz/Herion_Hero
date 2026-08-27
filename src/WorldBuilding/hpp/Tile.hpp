
#ifndef HERION_HERO_TILE_HPP
#define HERION_HERO_TILE_HPP

#include <SDL3/SDL.h>

#include "../../Textures/hpp/Texture.hpp"
#include "../../Utils/hpp/Logger.hpp"
class Tile {
  private:
    const Texture* texture;
    bool hasHitbox;
    SDL_FRect rect{};

  public:
    Tile();
    ~Tile();
    auto SetTexture(const Texture*) -> void;
    auto SetRect(float, float, float, float) -> void;
    auto Draw(SDL_Renderer*) const -> void;
    auto SetHitbox(bool) -> void;
    auto GetRect() -> SDL_FRect*;
    [[nodiscard]] auto HasHitbox() const -> bool;
    [[nodiscard]] auto GetCode() const -> std::string;
};

#endif // HERION_HERO_TILE_HPP
