#include "../hpp/Entity.hpp"
#include "JSONParser.hpp"
#include <string>

Entity::Entity() {
    this->componentes.clear();
}

void Entity::AddComponent(const std::string& name, ECS::Component* cmp) {
    if (componentes.contains(name))
        return;

    componentes.emplace(name, cmp);
}

void Entity::UpdateComponent(const std::string& name, ECS::Component* new_cmp) {
    if (!componentes.contains(name))
        return;
    componentes[name] = new_cmp;
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
    ECS::Rendering* rendering = static_cast<ECS::Rendering*>(componentes.at("rendering"));
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(componentes.at("sprite"));
    SDL_SetTextureBlendMode(sprite->current_frame.txt->GetTexture(), SDL_BLENDMODE_BLEND);
    SDL_RenderTexture(
        rendering->renderer, sprite->current_frame.txt->GetTexture(), nullptr, sprite->sprite_rect.to_sdl()
    );
}

void Entity::Move() {
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(componentes.at("sprites"));
    ECS::Velocites* velocities = static_cast<ECS::Velocites*>(componentes.at("velocities"));
    sprite->sprite_rect.Move(velocities->movement);
}

void Entity::Resize(const float scale) {
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(componentes.at("sprites"));
    sprite->sprite_rect.Resize(scale);
}

void Entity::Resize(const ECS::Vector2D& scale) {
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(componentes.at("sprites"));
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

    sprite->current_frame = sprite->animations_frames.at(animation_name + "_" + direction)[0];
    Texture* txt = sprite->current_frame.txt;

    float w, h;
    SDL_GetTextureSize(txt->GetTexture(), &w, &h);

    sprite->sprite_rect = {.size = {.dx = w, .dy = h}, .position = {.dx = 400, .dy = 400}};

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
    ECS::Sprites* sprites =
        new ECS::Sprites{.animations_frames = {}, .animations_data = {}, .current_frame = {}, .sprite_rect = {}};

    for (int i = 0; i < number_of_animations; i++) {

        JSONParser::animations::AnimationElementsFields animation_characteristic =
            JSONParser::animations::GetAnimationElementsFields(i);
        std::string animation_name = animation_characteristic.name;

        sprites->animations_data.emplace(
            animation_name,
            std::make_pair(animation_characteristic.frame_number, animation_characteristic.frame_to_load)
        );
        std::vector<ECS::Frame> frames;
        ECS::Rendering* rendering = static_cast<ECS::Rendering*>(componentes.at("rendering"));

        for (int j = 0; j < animation_characteristic.frame_to_load; j++) {
            std::string texture_name = animation_characteristic.path + "frame" + std::to_string(j) + ".png";
            frames.emplace_back(rendering->manager->GetTextureByName(texture_name));
        }

        sprites->animations_frames.emplace(animation_name, frames);
    }

    UpdateComponent("sprite", sprites);

    Logger::ClearTempLoggingFiles();
}
