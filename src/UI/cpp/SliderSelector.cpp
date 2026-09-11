//
// Created by tridoz on 22/05/26.
//

#include "../hpp/SliderSelector.hpp"
#include "ButtonsFunctions.hpp"
#include "JSONParser.hpp"
#include <functional>
#include <utility>

SliderSelector::SliderSelector() {
    this->slider_button_rect = {};
    this->slider_button_texture = nullptr;
    this->max_value = 0;
    this->min_value = 0;
    this->max_value_x = 0;
    this->min_value_x = 0;
    this->step = 0;
    this->is_updating = false;
}

SliderSelector::~SliderSelector() {
    StopUpdating();
}

auto SliderSelector::SetSliderButtonRect(SDL_FRect slider_rect) -> void {
    this->slider_button_rect = slider_rect;
}

auto SliderSelector::SetSliderButtonTexture(Texture* slider_texture) -> void {
    this->slider_button_texture = slider_texture;
}

auto SliderSelector::SetSliderBarRect(SDL_FRect slider_rect) -> void {
    this->slider_bar_rect = slider_rect;
}

auto SliderSelector::SetSliderBarTexture(Texture* slider_bar_texture) -> void {
    this->slider_bar_texture = slider_bar_texture;
}

auto SliderSelector::SetRenderable(std::vector<Renderable*> r) -> void {
    this->renderables = std::move(r);
}

auto SliderSelector::SetMaxMinStep(const float max, const float min, const float step) -> void {
    this->max_value = static_cast<int>(max);
    this->min_value = static_cast<int>(min);
    this->step = static_cast<float>(step);

    SetXValues(this->slider_bar_rect.x + this->slider_bar_rect.w, this->slider_bar_rect.x);
}

auto SliderSelector::SetToSet(std::string to_set) -> void {
    this->to_set = std::move(to_set);
}

auto SliderSelector::SaveVolume() -> void {

    float val_min = slider_bar_rect.x;
    float val_max = slider_bar_rect.x + slider_bar_rect.w;

    float button_center = slider_button_rect.x + slider_button_rect.w / 2.0f;

    float fixed_start = (button_center - val_min) * 100.0f / (val_max - val_min);

    if (to_set == "MASTER_VOLUME")
        JSONParser::audio::SetMasterVolume(static_cast<int>(std::round(fixed_start)));
    else if (to_set == "MUSIC_VOLUME")
        JSONParser::audio::SetMusicVolume(static_cast<int>(std::round(fixed_start)));
    else if (to_set == "SFX_VOLUME")
        JSONParser::audio::SetSFXVolume(static_cast<int>(std::round(fixed_start)));
}

auto SliderSelector::SetLength(float lenght) -> void {
    this->length = lenght;
}

auto SliderSelector::SetXValues(const float max, const float min) -> void {
    this->max_value_x = max;
    this->min_value_x = min;
}

auto SliderSelector::Draw(SDL_Renderer* renderer) const -> void {
    // for (int i = 0; i < this->renderables.size(); i++) {
    //     SDL_SetTextureBlendMode(renderables[i]->GetTexture()->GetTexture(), SDL_BLENDMODE_BLEND);
    //     SDL_RenderTexture(renderer, renderables[i]->GetTexture()->GetTexture(), nullptr, renderables[i]->GetRect());
    // }

    SDL_SetTextureBlendMode(this->slider_bar_texture->GetTexture(), SDL_BLENDMODE_BLEND);
    SDL_RenderTexture(renderer, this->slider_bar_texture->GetTexture(), nullptr, &slider_bar_rect);

    SDL_SetTextureBlendMode(this->slider_button_texture->GetTexture(), SDL_BLENDMODE_BLEND);
    SDL_RenderTexture(renderer, this->slider_button_texture->GetTexture(), nullptr, &slider_button_rect);
}

auto SliderSelector::GetSliderButtonRect(float mouse_x, float mouse_y) -> SDL_FRect* {
    SDL_FPoint p = {.x = mouse_x, .y = mouse_y};
    if (SDL_PointInRectFloat(&p, &slider_button_rect)) {
        return &this->slider_button_rect;
    }

    return nullptr;
}

auto SliderSelector::StartUpdating() -> void {
    is_updating = true;
}

auto SliderSelector::StopUpdating() -> void {
    is_updating = false;
}

auto SliderSelector::IsUpdating() const -> bool {
    return this->is_updating;
}

auto SliderSelector::SetOffsetX(float offsetX) -> void {
    if (offsetX < this->max_value_x && offsetX > this->min_value_x) {
        this->slider_button_rect.x = offsetX - slider_button_rect.w / 2;
    }
}

auto SliderSelector::SetOffsetY(float offsetY) -> void {
    this->offsetY = offsetY - slider_button_rect.y;
}

auto SliderSelector::GetMaxX() const -> float {
    return static_cast<float>(this->max_value_x);
}

auto SliderSelector::GetMinX() const -> float {
    return static_cast<float>(this->min_value_x);
}

auto SliderSelector::GetOffsetX() const -> float {
    return this->offsetX;
}

auto SliderSelector::GetOffsetY() const -> float {
    return this->offsetY;
}
