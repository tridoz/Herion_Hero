#ifndef HERION_HERO_TEXTURE_HPP
#define HERION_HERO_TEXTURE_HPP

#include <SDL3/SDL_image.h>
#include <SDL3/SDL.h>

#include <iostream>
#include <cmath>

#include "../../Utils/hpp/Logger.hpp"

class Texture {
    private:
        SDL_Texture* texture;
        std::string texture_name;
        const std::string base_path = "../";
        bool texture_created;
        std::string code;

    public:

        Texture();
        ~Texture();

        void CreateTexture( SDL_Renderer* renderer, const std::string& texture_to_create_name );
        [[nodiscard]] bool TextureCreated() const;
        [[nodiscard]] std::string GetTextureName() const;
        void operator=(const Texture& other);
        [[nodiscard]] SDL_Texture* GetTexture() const;
        void SetCode( const std::string& code );
        std::string GetCode() const;

        static constexpr auto reflect_members() {
            return std::tuple{
                Field<Texture, std::string>{"texture_name", &Texture::texture_name},
                Field<Texture, bool>{"texture_created", &Texture::texture_created},
                Field<Texture, std::string>{"code", &Texture::code},
            };
        }

};


#endif //HERION_HERO_TEXTURE_HPP
