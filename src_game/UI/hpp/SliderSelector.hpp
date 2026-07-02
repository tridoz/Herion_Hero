//
// Created by tridoz on 22/05/26.
//

#ifndef HERION_HERO_SLIDERSELECTOR_HPP
#define HERION_HERO_SLIDERSELECTOR_HPP

#include <SDL3/SDL.h>

#include <vector>
#include <thread>

#include "../../Textures/hpp/Texture.hpp"
#include "../../Utils/hpp/Logger.hpp"

class SliderSelector {
private:

    std::vector < Texture* > textures;
    std::vector < SDL_FRect > rects;

    bool is_updating;

    float offsetX, offsetY;

    Texture* slider_button_texture;
    SDL_FRect slider_button_rect;

    Texture* slider_bar_texture;
    SDL_FRect slider_bar_rect;

    int max_value;
    int min_value;

    float max_value_x;
    float min_value_x;

    float step;

public:
    SliderSelector();
    ~SliderSelector();

    void SetTextures( std::vector < Texture* > textures );
    void SetRects( std::vector < SDL_FRect > rects );

    void SetSliderButtonTexture( Texture* slider_texture );
    void SetSliderButtonRect( SDL_FRect slider_rect );

    void SetSliderBarTexture( Texture* slider_bar_texture );
    void SetSliderBarRect( SDL_FRect slider_rect );

    void SetMaxMinStep( float max, float min, float step );
    void SetXValues( float max, float min );

    [[nodiscard]] SDL_FRect* GetSliderButtonRect( float mouse_x, float mouse_y );

    void StartUpdating();
    void StopUpdating();


    void Draw( SDL_Renderer* renderer ) const;

    bool IsUpdating() const;

    void SetOffsetX( float offsetX );
    void SetOffsetY( float offsetY );

    float GetMaxX() const;

    float GetMinX() const;

    float GetOffsetX() const;
    float GetOffsetY() const;


};


#endif //HERION_HERO_SLIDERSELECTOR_HPP
