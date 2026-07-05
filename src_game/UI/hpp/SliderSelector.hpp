//
// Created by tridoz on 22/05/26.
//

#ifndef HERION_HERO_SLIDERSELECTOR_HPP
#define HERION_HERO_SLIDERSELECTOR_HPP

#include <SDL3/SDL.h>

#include <vector>
#include <thread>
#include<functional>

#include "../../Textures/hpp/Texture.hpp"
#include "../../Utils/hpp/Logger.hpp"

class SliderSelector {
private:

    std::vector < Texture* > textures;
    std::vector < SDL_FRect > rects;

    std::string to_set;

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
    float length;

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

    void SetLength( float lenght );

    void SaveVolume();

    void SetToSet(std::string to_set);

    float GetMaxX() const;

    float GetMinX() const;

    float GetOffsetX() const;
    float GetOffsetY() const;

    static constexpr auto reflect_members() {
        return std::make_tuple (
          Field<SliderSelector, std::vector<Texture*> > {"textures", &SliderSelector::textures},
          Field<SliderSelector, std::vector<SDL_FRect> > {"rects", &SliderSelector::rects},
          Field<SliderSelector, bool> {"is_updating", &SliderSelector::is_updating},
          Field<SliderSelector, float>{"offsetX", &SliderSelector::offsetX},
          Field<SliderSelector, float>{"offsetY", &SliderSelector::offsetY},
          Field<SliderSelector, Texture*>{"slider_button_texture", &SliderSelector::slider_button_texture},
          Field<SliderSelector, SDL_FRect>{"slider_button_rect", &SliderSelector::slider_button_rect},
          Field<SliderSelector, Texture*>{"slider_bar_texture", &SliderSelector::slider_bar_texture},
          Field<SliderSelector, SDL_FRect>{"slider_bar_rect", &SliderSelector::slider_bar_rect},
          Field<SliderSelector, int>{"max_value", &SliderSelector::max_value},
          Field<SliderSelector, int>{"min_value", &SliderSelector::min_value},
          Field<SliderSelector, float>{"max_value_x", &SliderSelector::max_value_x},
          Field<SliderSelector, float>{"min_value_x", &SliderSelector::min_value_x},
          Field<SliderSelector, float>{"step", &SliderSelector::step}
        );
    }


};


#endif //HERION_HERO_SLIDERSELECTOR_HPP
