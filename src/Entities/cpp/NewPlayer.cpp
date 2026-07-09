#include "../hpp/NewPlayer.hpp"

NewPlayer::NewPlayer() {
    AddComponent( "sprites", new ECS::Sprites );
    AddComponent( "rendering", new ECS::Rendering );
    AddComponent("transform", new ECS::Transform );
    AddComponent("velocities", new ECS::Velocites );
    AddComponent( "movement_state", new ECS::MovementState );
}
