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

    while ( (std::getline(texture_file, texture_name)) ) {
        if ( texture_name.empty() ) continue;

        Texture texture;
        try {
            texture.CreateTexture( renderer, texture_name );
        } catch ( HerionException::File::FileNotFoundException& ex ) {
            ex.UpdateStackTrace( GET_CONTEXT() );
            throw;
        }

        if ( texture.TextureCreated() ) {
            textures.insert( {texture_name, texture} );
        }

    }

}

Texture *TextureManager::GetTexture(const std::string &texture_name) {
    if ( textures.contains( texture_name) ) {
        return &textures.at( texture_name );
    }

    THROW_FILE_NOT_FOUND( texture_name );

}
