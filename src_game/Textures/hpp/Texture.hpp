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

    /**
     * @brief Create a texture based on the given path
     * @param renderer The renderer to creare the texture
     * @param texture_to_create_name The path of the texture file
     *@throw FILE_NOT_FOUND If the texture failed to create
     */
    void CreateTexture( SDL_Renderer* renderer, const std::string& texture_to_create_name );

    /**
     * @brief Return true or false ba on if the texture was successfully created or not
     * @return bool
     */
    [[nodiscard]] bool TextureCreated() const;

    /**
     * @brief Return the name of the texture
     * @return std::string
     */
    [[nodiscard]] std::string GetTextureName() const;

    /**
     * @brief The operator overloading to copy the texture
     * @param other The reference to the other texture to copy
     */
    void operator=(const Texture& other);

    /**
     * @brief Return the SDL_Texture field
     * @return SDL_Texture*
     */
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
