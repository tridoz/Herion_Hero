//
// Created by tridoz on 22/05/26.
//

#include "../hpp/SliderSelector.hpp"
#include "ButtonsFunctions.hpp"
#include "JSONParser.hpp"
#include <functional>

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

void SliderSelector::SetSliderButtonRect(SDL_FRect slider_rect) {
    this->slider_button_rect = slider_rect;
}

void SliderSelector::SetSliderButtonTexture(Texture* slider_texture) {
    this->slider_button_texture = slider_texture;
}

void SliderSelector::SetSliderBarRect(SDL_FRect slider_rect) {
    this->slider_bar_rect = slider_rect;
}

void SliderSelector::SetSliderBarTexture(Texture* slider_bar_texture) {
    this->slider_bar_texture = slider_bar_texture;
}

void SliderSelector::SetRenderable(std::vector<Renderable*> r) {
    this->renderables = r;
}

void SliderSelector::SetMaxMinStep(const float max, const float min, const float step) {
    this->max_value = max;
    this->min_value = min;
    this->step = step;

    // SetXValues(  this->rects[2].x, this->rects[0].x + this->rects[0].w  );
}

void SliderSelector::SetToSet(std::string to_set) {
    this->to_set = to_set;
}

void SliderSelector::SaveVolume() {
    int start = this->slider_button_rect.x + this->slider_button_rect.w / 2 - this->renderables[1]->GetRect()->x;

    if (to_set == "MASTER_VOLUME")
        JSONParser::audio::SetMasterVolume(std::clamp(start / 5, 0, 100));
    else if (to_set == "MUSIC_VOLUME")
        JSONParser::audio::SetMusicVolume(std::clamp(start / 5, 0, 100));
    else if (to_set == "SFX_VOLUME")
        JSONParser::audio::SetSFXVolume(std::clamp(start / 5, 0, 100));
}

void SliderSelector::SetLength(float lenght) {
    this->length = lenght;
}

void SliderSelector::SetXValues(const float max, const float min) {
    this->max_value_x = max;
    this->min_value_x = min;
}

void SliderSelector::Draw(SDL_Renderer* renderer) const {
    for (int i = 0; i < this->renderables.size(); i++) {
        SDL_SetTextureBlendMode(renderables[i]->GetTexture()->GetTexture(), SDL_BLENDMODE_BLEND);
        SDL_RenderTexture(renderer, renderables[i]->GetTexture()->GetTexture(), nullptr, renderables[i]->GetRect());
    }

    SDL_SetTextureBlendMode(this->slider_bar_texture->GetTexture(), SDL_BLENDMODE_BLEND);
    SDL_RenderTexture(renderer, this->slider_bar_texture->GetTexture(), nullptr, &slider_bar_rect);

    SDL_SetTextureBlendMode(this->slider_button_texture->GetTexture(), SDL_BLENDMODE_BLEND);
    SDL_RenderTexture(renderer, this->slider_button_texture->GetTexture(), nullptr, &slider_button_rect);
}

SDL_FRect* SliderSelector::GetSliderButtonRect(float mouse_x, float mouse_y) {
    if (mouse_x > slider_button_rect.x && mouse_x < slider_button_rect.x + slider_button_rect.w &&
        mouse_y > slider_button_rect.y && mouse_y < slider_button_rect.y + slider_button_rect.h) {
        return &this->slider_button_rect;
    }

    return nullptr;
}

void SliderSelector::StartUpdating() {
    is_updating = true;
}

void SliderSelector::StopUpdating() {
    this->is_updating = false;
}

bool SliderSelector::IsUpdating() const {
    return this->is_updating;
}

void SliderSelector::SetOffsetX(float offsetX) {
    if (offsetX < this->max_value_x && offsetX > this->min_value_x) {
        this->slider_button_rect.x = offsetX - slider_button_rect.w / 2;
    }
}

void SliderSelector::SetOffsetY(float offsetY) {
    this->offsetY = offsetY - slider_button_rect.y;
}

float SliderSelector::GetMaxX() const {
    return this->max_value;
}

float SliderSelector::GetMinX() const {
    return this->min_value;
}

float SliderSelector::GetOffsetX() const {
    return this->offsetX;
}

float SliderSelector::GetOffsetY() const {
    return this->offsetY;
}
