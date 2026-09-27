#include "../hpp/Player.hpp"

#include "../../Textures/hpp/TextureManager.hpp"
#include "../../Utils/hpp/JSONParser.hpp"
#include "HerionFileException.hpp"
#include "SDL3/SDL_render.h"
#include <chrono>
#include <stdexcept>

Player::Player() {
    this->AddComponent<ECS::Components::Transform>(new ECS::Components::Transform{
        .position = {.dx = 400, .dy = 400},
        .scale = {.dx = 1, .dy = 1},
        .rotation = 0,
        .facing_direction = ECS::states::FacingDirection::RIGHT
    });

    this->AddComponent<ECS::Components::Velocites>(
        new ECS::Components::Velocites{.jump = {.dx = 0, .dy = 0}, .movement = {.dx = 0, .dy = 0}}
    );

    this->AddComponent<ECS::Components::MovementState>(new ECS::Components::MovementState{
        .movement = ECS::states::Movements::IDLE,
        .is_grounded = true,
        .is_attached_wall_left = false,
        .is_attached_wall_right = false
    });

    this->AddComponent<ECS::Components::Sprites>(new ECS::Components::Sprites{
        .animations_frames = {},
        .animations_data = {},
        .last_update = 0,
        .current_frame = nullptr,
        .sprite_rect = {.size = {.dx = 0, .dy = 0}, .position = {.dx = 0, .dy = 0}}
    });
}

Player::~Player() {

    delete texture_manager;
    texture_manager = nullptr;
}

auto Player::SetTextureManager(TextureManager* new_texture_manager) -> void {
    this->texture_manager = new_texture_manager;
}

auto Player::Draw() -> void {
    auto rendering = GetComponent<ECS::Components::Rendering>();
    auto sprite = GetComponent<ECS::Components::Sprites>();
    auto transform = GetComponent<ECS::Components::Transform>();

    SDL_FRect dst = {
        .x = transform->position.dx - sprite->sprite_rect.size.dy / 2,
        .y = transform->position.dy - sprite->sprite_rect.size.dy,
        .w = sprite->sprite_rect.size.dx,
        .h = sprite->sprite_rect.size.dy
    };

    SDL_SetTextureBlendMode(sprite->current_frame->txt->GetTexture(), SDL_BLENDMODE_BLEND);
    SDL_RenderTexture(rendering->renderer, sprite->current_frame->txt->GetTexture(), nullptr, &dst);
}
