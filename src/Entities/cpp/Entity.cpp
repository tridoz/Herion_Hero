#include "../hpp/Entity.hpp"
#include "JSONParser.hpp"
#include <string>

Entity::Entity() {
    this->componentes.clear();
}

void Entity::Draw() {
    ECS::Components::Rendering* rendering = GetComponent<ECS::Components::Rendering>();
    ECS::Components::Sprites* sprite = GetComponent<ECS::Components::Sprites>();
    SDL_SetTextureBlendMode(sprite->current_frame->txt->GetTexture(), SDL_BLENDMODE_BLEND);
    SDL_RenderTexture(
        rendering->renderer, sprite->current_frame->txt->GetTexture(), nullptr, sprite->sprite_rect.to_sdl()
    );
}

void Entity::Move() {
    ECS::Components::Sprites* sprite = GetComponent<ECS::Components::Sprites>();
    ECS::Components::Velocites* velocities = GetComponent<ECS::Components::Velocites>();
    ECS::Components::Transform* transform = GetComponent<ECS::Components::Transform>();
    ECS::Components::MovementState* movements = GetComponent<ECS::Components::MovementState>();
    transform->position = transform->position + velocities->movement;
    transform->position = transform->position + velocities->jump;

    sprite->sprite_rect.Move(velocities->movement);
    sprite->sprite_rect.Move(velocities->jump);

    if (movements->is_jumping) {
        ECS::Math::ApplyGravity(velocities);
    }

    this->UpdateComponent<ECS::Components::Sprites>(sprite);
    this->UpdateComponent<ECS::Components::Velocites>(velocities);
}

void Entity::Resize(const float scale) {
    ECS::Components::Sprites* sprite = GetComponent<ECS::Components::Sprites>();
    sprite->sprite_rect.Resize(scale);
}

void Entity::Resize(const ECS::Components::Vector2D& scale) {
    ECS::Components::Sprites* sprite = GetComponent<ECS::Components::Sprites>();
    sprite->sprite_rect.Resize(scale);
}

void Entity::UpdateFrame() {
    ECS::Components::Sprites* sprite = GetComponent<ECS::Components::Sprites>();
    ECS::Components::MovementState* movement_state = GetComponent<ECS::Components::MovementState>();
    ECS::Components::Transform* transform = GetComponent<ECS::Components::Transform>();

    std::string direction;
    std::string animation_name;

    switch (transform->facing_direction) {
    case ECS::states::FacingDirection::LEFT:
        direction = "LEFT";
        break;
    case ECS::states::FacingDirection::RIGHT:
        direction = "RIGHT";
        break;
    }

    switch (movement_state->movement) {
    case ECS::states::Movements::IDLE:
        animation_name = "IDLE";
        break;

    case ECS::states::Movements::RUN:
        animation_name = "RUN";
        break;

    case ECS::states::Movements::FALLING:
        animation_name = "FALL";
        break;

    case ECS::states::Movements::JUMPING:
        animation_name = "JUMP";
        break;
    }

    std::vector<ECS::Frame*> frames = sprite->animations_frames.at(animation_name + "_" + direction);
    std::pair<int, int> frame_data = sprite->animations_data.at(animation_name + "_" + direction);

    int frame_number = frame_data.first;

    sprite->last_update += delta_time;

    std::size_t index;
    if (sprite->current_frame == nullptr) {
        index = 0;
        sprite->current_frame = sprite->animations_frames.at(animation_name + "_" + direction)[index];
        sprite->last_update = 0;
    } else {
        index = (std::distance(frames.begin(), std::find(frames.begin(), frames.end(), sprite->current_frame)) + 1) %
                frames.size();

        if (sprite->last_update > (delta_time * static_cast<float>(frame_number))) {
            sprite->current_frame = sprite->animations_frames.at(animation_name + "_" + direction)[index];
            sprite->last_update = 0;
        }
    }

    Texture* txt = sprite->current_frame->txt;

    float w, h;
    SDL_GetTextureSize(txt->GetTexture(), &w, &h);

    sprite->sprite_rect.size = {.dx = w, .dy = h};

    UpdateComponent<ECS::Components::Sprites>(sprite);
}

void Entity::LoadSprites(const std::string& filepath) {

    try {
        JSONParser::animations::SetConfigFile(filepath);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    int number_of_animations = JSONParser::animations::GetAnimationNumbers();
    ECS::Components::Sprites* sprites = GetComponent<ECS::Components::Sprites>();

    for (int i = 0; i < number_of_animations; i++) {

        JSONParser::animations::AnimationElementsFields animation_characteristic =
            JSONParser::animations::GetAnimationElementsFields(i);
        std::string animation_name = animation_characteristic.name;

        sprites->animations_data.emplace(
            animation_name,
            std::make_pair(animation_characteristic.frame_number, animation_characteristic.frame_to_load)
        );
        std::vector<ECS::Frame*> frames;
        ECS::Components::Rendering* rendering = GetComponent<ECS::Components::Rendering>();
        for (int j = 0; j < animation_characteristic.frame_to_load; j++) {
            std::string texture_name = animation_characteristic.path + "frame" + std::to_string(j) + ".png";
            frames.emplace_back(new ECS::Frame{.txt = rendering->manager->GetTextureByName(texture_name)});
        }

        sprites->animations_frames.emplace(animation_name, frames);
    }

    UpdateComponent<ECS::Components::Sprites>(sprites);

    Logger::ClearTempLoggingFiles();
}

void Entity::SetDeltaTime(float delta) {
    this->delta_time = delta;
}

float Entity::GetDeltaTime() const {
    return this->delta_time;
}