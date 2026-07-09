#include "../hpp/Entity.hpp"
#include "JSONParser.hpp"
#include <string>

Entity::Entity() {
    this->componentes.clear();
}

void Entity::AddComponent( const std::string& name, ECS::Component * cmp ) {
    if( componentes.contains(name ) )
        return;

    componentes.emplace(name, cmp );
}

void Entity::UpdateComponent( const std::string& name, ECS::Component* new_cmp ) {
    if( !componentes.contains(name) )
        return;
    componentes[name] = new_cmp;
}

ECS::Component* Entity::GetComponent( const std::string& name ) {
    if( this->componentes.contains(name) )
        return this->componentes.at(name);

    return nullptr;
}

bool Entity::HasComponent( const std::string& name ) {
    return this->componentes.contains(name);
}

void Entity::Draw( SDL_Renderer* renderer ) {
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(componentes.at("sprites") );
    SDL_SetTextureBlendMode( sprite->current_frame.txt->GetTexture(), SDL_BLENDMODE_BLEND );
    SDL_RenderTexture( renderer, sprite->current_frame.txt->GetTexture(), nullptr, sprite->sprite_rect.to_sdl() );
}

void Entity::Move() {
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(componentes.at("sprites") );
    ECS::Velocites* velocities = static_cast<ECS::Velocites*>(componentes.at("velocities") );
    sprite->sprite_rect.Move( velocities->movement );
}

void Entity::Resize( const float scale ) {
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(componentes.at("sprites") );
    sprite->sprite_rect.Resize(scale);
}

void Entity::Resize( const ECS::Vector2D& scale ) {
    ECS::Sprites* sprite = static_cast<ECS::Sprites*>(componentes.at("sprites") );
    sprite->sprite_rect.Resize(scale);
}

void Entity::LoadSprites( const std::string& filepath ) {

    try {
        JSONParser::animations::SetConfigFile( filepath );
    } catch( HerionException::File::FileException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        throw;
    }

    int number_of_animations = JSONParser::animations::GetAnimationNumbers();
    ECS::Sprites* sprites{};

    for( int i = 0 ; i<number_of_animations ; i++ ) {

        JSONParser::animations::AnimationElementsFields animation_characteristic = JSONParser::animations::GetAnimationElementsFields( i );
        std::string animation_name = animation_characteristic.name;
        sprites->animations_data.emplace(animation_name, std::make_pair(animation_characteristic.frame_number, animation_characteristic.frame_to_load) );
        std::vector<ECS::Frame> frames;
        ECS::Rendering* rendering = static_cast<ECS::Rendering*>(componentes.at("rendering") );

        for( int j = 0 ; j < animation_characteristic.frame_to_load ; j++ ) {
            std::string texture_name = animation_characteristic.path + "frame" + std::to_string(j) + ".png";
            frames.emplace_back( rendering->manager->GetTextureByName( texture_name ) );
        }

        sprites->animations_frames.emplace(animation_name, frames);

    }

    AddComponent( "sprites", sprites );


}
