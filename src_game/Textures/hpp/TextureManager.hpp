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
    const std::string base_path = "../";
public:

    TextureManager();
    void LoadTextures( const std::string& filepath );
    void SetRenderer( SDL_Renderer* renderer ) ;
    Texture GetTexture( const std::string& texture_name );

};


#endif //HERION_HERO_TEXTUREMANAGER_HPP