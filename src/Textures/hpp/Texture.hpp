#ifndef HERION_HERO_TEXTURE_HPP
#define HERION_HERO_TEXTURE_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include <cmath>
#include <iostream>

#include "../../Utils/hpp/Logger.hpp"

class Texture {
  private:
    SDL_Texture* texture;
    std::string texture_name;
    const std::string base_path = "../";
    bool texture_created;
    std::string code;

  public:
    Texture();
    ~Texture();

    auto CreateTexture(SDL_Renderer*, const std::string&) -> void;
    [[nodiscard]] auto TextureCreated() const -> bool;
    [[nodiscard]] auto GetTextureName() const -> std::string;
    [[nodiscard]] auto GetTexture() const -> SDL_Texture*;
    auto SetCode(const std::string&) -> void;
    [[nodiscard]] auto GetCode() const -> std::string;
};

#endif // HERION_HERO_TEXTURE_HPP
