//
// Created by david on 17/11/2025.
//

#include "../hpp/Texture.hpp"

#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "../hpp/TextureManager.hpp"

Texture::Texture() {
    texture = nullptr;
    texture_name = "";
    texture_created = false;
}

Texture::~Texture() {
    texture = nullptr;
    texture_name = "";
    texture_created = false;
}

auto Texture::CreateTexture(SDL_Renderer* renderer, const std::string& texture_to_create_name) -> void {

    this->texture_name = texture_to_create_name;

    this->texture = IMG_LoadTexture(renderer, this->texture_name.c_str());

    if (!this->texture) {
        this->texture = IMG_LoadTexture(renderer, ("../" + this->texture_name).c_str());
    }

    if (!this->texture) {
        THROW_FILE_NOT_FOUND((this->texture_name + " nor ../" + this->texture_name));
    }

    texture_created = true;
}

auto Texture::TextureCreated() const -> bool {
    return texture_created;
}

auto Texture::GetTexture() const -> SDL_Texture* {
    return texture;
}

auto Texture::GetTextureName() const -> std::string {
    return texture_name;
}

auto Texture::SetCode(const std::string& code) -> void {
    this->code = code;
}

auto Texture::GetCode() const -> std::string {
    return code;
}
