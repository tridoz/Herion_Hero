//
// Created by david on 16/11/2025.
//

#include "TextureManager.hpp"

TextureManager::TextureManager()  {
    this->renderer = nullptr;
    textures.clear();
}

void TextureManager::SetRenderer(SDL_Renderer* renderer)  {
    this->renderer = renderer;
}

void TextureManager::LoadTextures( const std::string& filepath ) {


    std::ifstream texture_file( base_path + filepath, std::ios::in) ;

    if ( !texture_file.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "LOADING",
            "TextureManager",
            "LoadTextures",
            strerror(errno)
            );
        return;
    }

    Logger::LogOK(
        std::time(nullptr),
        "LOADING",
        "TextureManager",
        "LoadTextures",
        "Texture file opened successfully"
        );

    std::string texture_name = "";

    while ( (std::getline(texture_file, texture_name)) ) {

        Texture texture;
        texture.CreateTexture( renderer, texture_name );

        if ( texture.TextureCreated() ) {
            textures.insert( {texture_name, texture} );
        }

    }

}

Texture TextureManager::GetTexture( const std::string& texture_name ) {
    return textures.at( texture_name );
}
