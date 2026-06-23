//
// Created by david on 17/11/2025.
//

#include "../hpp/Texture.hpp"

#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "../hpp/TextureManager.hpp"

Texture::Texture()  {
    texture = nullptr;
    texture_name = "";
    texture_created = false;
}

Texture::~Texture() {
    texture = nullptr;
    texture_name = "";
    texture_created = false;
}


void Texture::CreateTexture( SDL_Renderer* renderer, const std::string& texture_to_create_name ) {

    this->texture_name = texture_to_create_name;

    this->texture = IMG_LoadTexture( renderer, this->texture_name.c_str() );

    if ( !this->texture ) {
        THROW_FILE_NOT_FOUND( this->texture_name );
    }

    texture_created = true;

}

bool Texture::TextureCreated() const {
    return texture_created;
}

SDL_Texture* Texture::GetTexture() const {
    return texture;
}

std::string Texture::GetTextureName() const {
    return texture_name;
}


void Texture::operator=(const Texture& other) {
    this->texture = other.texture;
    this->texture_name = other.texture_name;
    this->texture_created = other.texture_created;
}

void Texture::SetCode( const std::string& code ) {
    this->code = code;
}

std::string Texture::GetCode() const {
    return code;
}
