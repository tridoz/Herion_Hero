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

    std::unordered_map<std::string, Texture > textures;
    const std::string base_path = "../";
public:

    TextureManager();

    ~TextureManager();

    /**
     * @brief   Load all the textures in an std::unordered_map<std::string, Textured> based
     *          of a .txt file with all the textures path written in it.
     * @param filepath The filepath to the loader file.
     * @throw HerionException::File::FileException if the loader file opening failed.
     * @throw HerionException::File::FileNotFoundException if the texture file wasn't found.
     */
    void LoadTextures( const std::string& filepath );

    /**
     * @brief Set the SDL_Renderer*.
     * @param new_renderer The renderer to set.
     */
    void SetRenderer( SDL_Renderer* new_renderer ) ;

    /**
     * @brief Return a pointer to the Texture based on the name given.
     * @param texture_name The name of the texture to return.
     * @throws HerionHexception::File::FileNotFound if the texture doesn't exists.
     * @return Texture*
     */
    Texture *GetTexture(const std::string &texture_name);

};


#endif //HERION_HERO_TEXTUREMANAGER_HPP