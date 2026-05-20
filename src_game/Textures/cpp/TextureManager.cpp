//
// Created by david on 16/11/2025.
//

#include "../hpp/TextureManager.hpp"
#include "../../Utils/hpp/FileOpener.hpp"

TextureManager::TextureManager()  {
    this->renderer = nullptr;
    textures.clear();
}

TextureManager::~TextureManager() {
    for ( auto pair : textures ) {
        SDL_DestroyTexture( pair.second.GetTexture() );
    }
}

void TextureManager::SetRenderer( SDL_Renderer* new_renderer )  {
    this->renderer = new_renderer;
}

void TextureManager::LoadTextures( const std::string& filepath ) {

    std::ifstream texture_file;

    try {
        FileOpener::OpenFileInput( texture_file, base_path + filepath );
    } catch ( HerionException::File::FileException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        throw;
    }

    std::string texture_name;
    std::string texture_code;
    std::string line;

    while ( (std::getline(texture_file, line)) ) {
        if ( line.empty() ) continue;

        size_t pos = line.find(';');

        texture_name = line.substr( 0, pos );
        texture_code = line.substr( pos + 1 );

        codes.emplace( texture_code, texture_name );

        Texture texture;
        try {
            texture.CreateTexture( renderer, texture_name );
            texture.SetCode( texture_code );
        } catch ( HerionException::File::FileNotFoundException& ex ) {
            ex.UpdateStackTrace( GET_CONTEXT() );
            throw;
        }

        if ( texture.TextureCreated() ) {
            textures.insert( {texture_name, texture} );
        }

    }

}

Texture *TextureManager::GetTextureByName(const std::string &texture_name) {

    if ( !textures.contains( texture_name) ) {
        THROW_FILE_NOT_FOUND( texture_name );
    }

    return &textures.at( texture_name );

}

Texture *TextureManager::GetTextureByCode(const std::string &texture_code) {

    if ( !codes.contains( texture_code) ) {
        THROW_FILE_NOT_FOUND( texture_code );
    }

    return &textures.at( codes.at( texture_code ) );

}
