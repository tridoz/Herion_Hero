#ifndef HERION_HERO_TEXTUREMANAGER_HPP
#define HERION_HERO_TEXTUREMANAGER_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>

#include <fstream>
#include <sstream>

#include <unordered_map>

#include "../../Utils/hpp/Logger.hpp"
#include "Texture.hpp"

class TextureManager {

  private:
    SDL_Renderer* renderer;

    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, std::string> codes;
    const std::string base_path = "../";

  public:
    TextureManager();
    ~TextureManager();

    auto LoadTextures(const std::string&) -> void;
    auto SetRenderer(SDL_Renderer*) -> void;
    auto GetTextureByName(const std::string&) -> Texture*;
    auto GetTextureByCode(const std::string&) -> Texture*;
};

#endif // HERION_HERO_TEXTUREMANAGER_HPP
