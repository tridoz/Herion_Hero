//
// Created by trida on 11/29/25.
//

#ifndef HERION_HERO_ANIMATION_HPP
#define HERION_HERO_ANIMATION_HPP

#include <vector>

#include "../../Textures/hpp/Texture.hpp"

class Animation {
  private:
    std::vector<Texture*> animation_textures;

    int frame_rate;
    int frame_number;
    int current_animation_frame;
    float how_often_frame_update;
    float frame_duration;

    time_t last_update_time;
    time_t current_time;

  public:
    Animation();

    auto AddFrameTexture(Texture*) -> void;
    [[nodiscard]] auto GetCurrentFrameTexture() const -> Texture*;
    auto Update() -> void;
    auto SetFrameRate(int) -> void;
    auto SetAnimationFrameNUmber(int) -> void;
    [[nodiscard]] auto GetCurrentFrameTextureHeight() const -> float;
    [[nodiscard]] auto GetCurrentFrameTextureWidth() const -> float;
};

#endif // HERION_HERO_ANIMATION_HPP
