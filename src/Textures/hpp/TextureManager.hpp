#ifndef HERION_HERO_TEXTUREMANAGER_HPP
#define HERION_HERO_TEXTUREMANAGER_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>

#include <fstream>
#include <sstream>

#include <unordered_map>

#include "../../Utils/hpp/Logger.hpp"
#include "../../Utils/hpp/Reflector.hpp"
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

    void LoadTextures(const std::string& filepath);
    void SetRenderer(SDL_Renderer* new_renderer);
    Texture* GetTextureByName(const std::string& texture_name);
    Texture* GetTextureByCode(const std::string& texture_code);

    static constexpr auto reflect_members() {
        return std::make_tuple(
            Field<TextureManager, SDL_Renderer*>{"renderer", &TextureManager::renderer},
            Field<TextureManager, std::unordered_map<std::string, Texture>>{"textures", &TextureManager::textures},
            Field<TextureManager, std::unordered_map<std::string, std::string>>{"codes", &TextureManager::codes}
        );
    }
};

#endif // HERION_HERO_TEXTUREMANAGER_HPP
