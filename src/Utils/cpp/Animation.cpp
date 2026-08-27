//
// Created by trida on 11/29/25.
//

#include "../hpp/Animation.hpp"

Animation::Animation() {
    last_update_time = static_cast<Uint32>(SDL_GetTicks());
    current_animation_frame = 0;
}

auto Animation::AddFrameTexture(Texture* new_texture) -> void {
    animation_textures.push_back(new_texture);
}

[[nodiscard]] auto Animation::GetCurrentFrameTexture() const -> Texture* {
    return animation_textures[current_animation_frame];
}

auto Animation::Update() -> void {
    current_time = static_cast<Uint32>(SDL_GetTicks());
    if (static_cast<float>(current_time - last_update_time) > how_often_frame_update) {
        current_animation_frame++;
        current_animation_frame %= static_cast<int>(animation_textures.size());
        last_update_time = current_time;
    }
}

auto Animation::SetFrameRate(int new_frame_rate) -> void {
    this->frame_rate = new_frame_rate;
    this->how_often_frame_update = 1000.0f / static_cast<float>(frame_rate);
}

auto Animation::SetAnimationFrameNUmber(int new_frame_number) -> void {
    this->frame_number = new_frame_number;
}

[[nodiscard]] auto Animation::GetCurrentFrameTextureHeight() const -> float {
    float w, h;
    SDL_GetTextureSize(animation_textures[current_animation_frame]->GetTexture(), &w, &h);
    return h;
}

[[nodiscard]] auto Animation::GetCurrentFrameTextureWidth() const -> float {
    float w, h;
    SDL_GetTextureSize(animation_textures[current_animation_frame]->GetTexture(), &w, &h);
    return w;
}
