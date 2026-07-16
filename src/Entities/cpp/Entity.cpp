#include "../hpp/Entity.hpp"
#include "JSONParser.hpp"
#include <string>

Entity::Entity() {
    this->componentes.clear();
}

void Entity::AddComponent(const std::string& name, ECS::Component* cmp) {
    if (this->componentes.contains(name))
        return;

    this->componentes.emplace(name, cmp);
}

void Entity::UpdateComponent(const std::string& name, ECS::Component* new_cmp) {
    if (!this->componentes.contains(name))
        return;
    this->componentes[name] = new_cmp;
}

ECS::Component* Entity::GetComponent(const std::string& name) {
    if (this->componentes.contains(name))
        return this->componentes.at(name);

    return nullptr;
}

bool Entity::HasComponent(const std::string& name) {
    return this->componentes.contains(name);
}

void Entity::Draw() {
    ECS::Rendering* rendering = static_cast<ECS::Rendering*>(this->componentes.at("rendering"));
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(this->componentes.at("sprite"));
    SDL_SetTextureBlendMode(sprite->current_frame->txt->GetTexture(), SDL_BLENDMODE_BLEND);
    SDL_RenderTexture(
        rendering->renderer, sprite->current_frame->txt->GetTexture(), nullptr, sprite->sprite_rect.to_sdl()
    );
}

void Entity::Move() {
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(componentes.at("sprite"));
    ECS::Velocites* velocities = static_cast<ECS::Velocites*>(componentes.at("velocity"));
    ECS::Transform* transform = static_cast<ECS::Transform*>(componentes.at("transform"));

    transform->position = transform->position + velocities->movement;
    sprite->sprite_rect.Move(velocities->movement);

    this->UpdateComponent("sprite", sprite);
}

void Entity::Resize(const float scale) {
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(componentes.at("sprite"));
    sprite->sprite_rect.Resize(scale);
}

void Entity::Resize(const ECS::Vector2D& scale) {
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(componentes.at("sprite"));
    sprite->sprite_rect.Resize(scale);
}

void Entity::UpdateFrame() {
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(componentes.at("sprite"));
    ECS::MovementState* movement_state = static_cast<ECS::MovementState*>(componentes.at("movement_state"));
    ECS::Transform* transform = static_cast<ECS::Transform*>(componentes.at("transform"));

    std::string direction;
    std::string animation_name;

    switch (transform->facing_direction) {
    case ECS::FacingDirection::LEFT:
        direction = "LEFT";
        break;
    case ECS::FacingDirection::RIGHT:
        direction = "RIGHT";
        break;
    }

    switch (movement_state->movement) {
    case ECS::Movements::IDLE:
        animation_name = "IDLE";
        break;

    case ECS::Movements::RUN:
        animation_name = "RUN";
        break;

    case ECS::Movements::FALLING:
        animation_name = "FALL";
        break;

    case ECS::Movements::JUMPING:
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

    UpdateComponent("sprite", sprite);
}

void Entity::LoadSprites(const std::string& filepath) {

    try {
        JSONParser::animations::SetConfigFile(filepath);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    int number_of_animations = JSONParser::animations::GetAnimationNumbers();
    ECS::Sprites* sprites = static_cast<ECS::Sprites*>(componentes.at("sprite"));

    for (int i = 0; i < number_of_animations; i++) {

        JSONParser::animations::AnimationElementsFields animation_characteristic =
            JSONParser::animations::GetAnimationElementsFields(i);
        std::string animation_name = animation_characteristic.name;

        sprites->animations_data.emplace(
            animation_name,
            std::make_pair(animation_characteristic.frame_number, animation_characteristic.frame_to_load)
        );
        std::vector<ECS::Frame*> frames;
        ECS::Rendering* rendering = static_cast<ECS::Rendering*>(componentes.at("rendering"));

        for (int j = 0; j < animation_characteristic.frame_to_load; j++) {
            std::string texture_name = animation_characteristic.path + "frame" + std::to_string(j) + ".png";
            frames.emplace_back(new ECS::Frame{.txt = rendering->manager->GetTextureByName(texture_name)});
        }

        sprites->animations_frames.emplace(animation_name, frames);
    }

    UpdateComponent("sprite", sprites);

    Logger::ClearTempLoggingFiles();
}

void Entity::SetDeltaTime(float delta) {
    this->delta_time = delta;
}

float Entity::GetDeltaTime() const {
    return this->delta_time;
}