//
// Created by tridoz on 22/05/26.
//

#ifndef HERION_HERO_SLIDERSELECTOR_HPP
#define HERION_HERO_SLIDERSELECTOR_HPP

#include <SDL3/SDL.h>

#include <functional>
#include <thread>
#include <vector>

#include "../../Textures/hpp/Renderable.hpp"
#include "../../Utils/hpp/Logger.hpp"

class SliderSelector {
  private:
    std::vector<Renderable*> renderables;

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

    auto SetRenderable(std::vector<Renderable*>) -> void;
    auto SetSliderButtonTexture(Texture*) -> void;
    auto SetSliderButtonRect(SDL_FRect) -> void;
    auto SetSliderBarTexture(Texture*) -> void;
    auto SetSliderBarRect(SDL_FRect) -> void;
    auto SetMaxMinStep(float, float, float) -> void;
    auto SetXValues(float, float) -> void;
    [[nodiscard]] auto GetSliderButtonRect(float, float) -> SDL_FRect*;
    auto StartUpdating() -> void;
    auto StopUpdating() -> void;
    auto Draw(SDL_Renderer*) const -> void;
    [[nodiscard]] auto IsUpdating() const -> bool;
    auto SetOffsetX(float) -> void;
    auto SetOffsetY(float) -> void;
    auto SetLength(float) -> void;
    auto SaveVolume() -> void;
    auto SetToSet(std::string) -> void;
    [[nodiscard]] auto GetMaxX() const -> float;
    [[nodiscard]] auto GetMinX() const -> float;
    [[nodiscard]] auto GetOffsetX() const -> float;
    [[nodiscard]] auto GetOffsetY() const -> float;
};

#endif // HERION_HERO_SLIDERSELECTOR_HPP
