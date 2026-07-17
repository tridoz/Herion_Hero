#include "../hpp/Player.hpp"

#include "../../Textures/hpp/TextureManager.hpp"
#include "../../Utils/hpp/JSONParser.hpp"
#include "HerionFileException.hpp"
#include <stdexcept>

Player::Player() {
    this->AddComponent(
        "transform",
        new ECS::Components::Transform{
            .position = {.dx = 0, .dy = 0},
            .scale = {.dx = 1, .dy = 1},
            .rotation = 0,
            .facing_direction = ECS::states::FacingDirection::RIGHT
        }
    );

    this->AddComponent(
        "velocity", new ECS::Components::Velocites{.jump = {.dx = 0, .dy = 0}, .movement = {.dx = 0, .dy = 0}}
    );

    this->AddComponent(
        "movement_state",
        new ECS::Components::MovementState{
            .movement = ECS::states::Movements::IDLE,
            .is_grounded = false,
            .is_attached_wall_left = false,
            .is_attached_wall_right = false
        }
    );

    this->AddComponent(
        "sprite",
        new ECS::Components::Sprites{
            .animations_frames = {},
            .animations_data = {},
            .last_update = 0,
            .current_frame = nullptr,
            .sprite_rect = {.size = {.dx = 0, .dy = 0}, .position = {.dx = 400, .dy = 400}}
        }
    );
}

Player::~Player() {

    delete texture_manager;
    texture_manager = nullptr;
}

void Player::SetTextureManager(TextureManager* new_texture_manager) {
    this->texture_manager = new_texture_manager;
}
