#ifndef HERION_HERO_TEXTURE_HPP
#define HERION_HERO_TEXTURE_HPP

#include <SDL3/SDL_image.h>
#include <SDL3/SDL.h>


#include <iostream>
#include <cmath>

#include "../Helpers/Logger.hpp"


class Texture {

private:
    SDL_Texture* texture;
    std::string texture_name;
    const std::string base_path = "../";
    bool texture_created;
public:

    Texture();
    ~Texture();

    void CreateTexture( SDL_Renderer* renderer, const std::string& texture_name );
    [[nodiscard]] bool TextureCreated() const;
    std::string GetTextureName() const;

    void operator=(const Texture& other);

    [[nodiscard]] SDL_Texture* GetTexture() const;

};


#endif //HERION_HERO_TEXTURE_HPP