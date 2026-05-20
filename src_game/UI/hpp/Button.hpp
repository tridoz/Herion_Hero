//
// Created by david on 21/11/2025.
//

#ifndef HERION_HERO_BUTTON_HPP
#define HERION_HERO_BUTTON_HPP

#include <functional>
#include <SDL3/SDL.h>

#include "../../Textures/hpp/Texture.hpp"
#include "../../Utils/hpp/Logger.hpp"



class Button {
private:
    std::function<void()> OnClick;
    std::function<std::string()> OnClickReturn;

    std::vector< Texture* > textures;
    std::vector< SDL_FRect > rects ;

    std::string text;

public:

    Button();

    /**
     * @brief Set the "action listenere function" for the button
     * @param action Function to execute when button clicked
     */
    void SetOnClick(std::function<void()> action);

    void SetOnClickReturn( std::function<std::string()> action );

    /**
     * @brief Execute the function
     */
    void Click() const;
    std::string ClickReturn() const;

    /**
     * @brief Set the Texture of the Button
     * @param textures Textures to set
     */
    void SetTextures( std::vector< Texture* > textures );

    /**
     * @brief Set the SDL_FRects of the Button
     * @param rects SDL_FRects to set
     */
    void SetRects( std::vector< SDL_FRect > rects );

    /**
     * @brief Draw the Button with its coordinates
     * @param renderer renderer needed to draw
     */
    void Draw( SDL_Renderer* renderer ) const ;

    /**
     * @brief Draw the Button shifted of an offset and only if in certain coordinates
     * @param renderer Renderer needed to draw
     * @param offset_y Offset Y to add to the coordinates
     * @param offset_x Offset X to add to the coodinates
     */
    void DrawWithOffset( SDL_Renderer* renderer, const float offset_y, const float offset_x ) const ;

    /**
     * @brief Return the Button's rects
     * @return std::vector < SDL_FRect >
     */
    std::vector< SDL_FRect > GetRects() const;

    void SetText( const std::string& text_to_set );

    std::string GetText() const ;
};


#endif //HERION_HERO_BUTTON_HPP