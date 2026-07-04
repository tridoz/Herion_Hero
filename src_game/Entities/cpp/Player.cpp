//
// Created by trida on 11/19/25.
//

#include "../hpp/Player.hpp"

#include "../../Textures/hpp/TextureManager.hpp"
#include "../../Utils/hpp/JSONParser.hpp"
#include "SDL3/SDL_camera.h"


Player::Player() {

	this->mode = GameMode::IN_GAME;
	this->state = PlayerState::IDLE;
	this->direction = FacingDirection::EAST;



	this->velocity_x = 0.0f;
	this->speed = 500;

	this->player_rect.w = 30;
	this->player_rect.h = 60;

	this->player_rect = {pos_x, pos_y, pos_x, pos_y};

	this->fixed_pos_x = this->pos_x;
	this->fixed_pos_y = this->pos_y;

	this->scale = JSONParser::graphics::GetScale();

	animations.emplace( "IDLE_LEFT", new Animation() );
	animations.emplace( "IDLE_RIGHT", new Animation() );

	animations.emplace("RUN_LEFT", new Animation() );
	animations.emplace("RUN_RIGHT", new Animation() );

	animations.emplace( "JUMP_LEFT", new Animation() );
	animations.emplace( "JUMP_RIGHT", new Animation() );

	animations.emplace("FALL_LEFT", new Animation() );
	animations.emplace("FALL_RIGHT", new Animation() );

	animations.emplace("WALL_LEFT", new Animation() );
	animations.emplace("WALL_RIGHT", new Animation() );

	current_animation = animations.at("IDLE_RIGHT");

}

Player::~Player() {
	this->mode = GameMode::MAIN_MENU;
	this->state = PlayerState::IDLE;
}

Player::GameMode Player::GetGameMode() const {
	return mode;
}

Player::PlayerState Player::GetPlayerState() const {
	return state;
}

Player::FacingDirection Player::GetDirection() const {
	return direction;
}

Player::PlayerState Player::GetPreviousState() const {
	return previousState;
}

Player::GameMode Player::GetPreviousGameMode() const {
	return previousGameMode;
}

void Player::SetPlayerState( const PlayerState new_player_state ) {
	this->previousState = this->state;
	this->state = new_player_state;
}


void Player::SetGameMode( const GameMode new_game_mode ) {
	this->previousGameMode = this->mode;
	this->mode = new_game_mode;
}

void Player::SetPlayerDirection( const FacingDirection new_direction) {
	this->direction = new_direction;
	std::string str_state = "";
	std::string str_direction = "";

	switch ( this->state ) {
		default:
			break;

		case PlayerState::IDLE:
			str_state = "IDLE_";
			break;

		case PlayerState::RUN:
			str_state = "RUN_";
			break;

		case PlayerState::JUMP:
			str_state = "JUMP_";
			break;

		case PlayerState::FALLING:
			str_state = "FALL_";

	}

	switch ( new_direction ) {
		case FacingDirection::WEST:
			str_direction = "LEFT";
			break;

		case FacingDirection::EAST:
			str_direction = "RIGHT";
			break;
	}

	if ( !animations.contains( str_state + str_direction ) ) {
		THROW_FILE_NOT_FOUND( str_state + str_direction );
	}

	current_animation = animations.at( str_state + str_direction );

}

void Player::SetTextureManager( TextureManager *new_texture_manager ) {
	this->texture_manager = new_texture_manager;
}

void Player::LoadAnimation( const std::string &filepath ) {

	try {
		JSONParser::animations::SetConfigFile( filepath );
	} catch ( HerionException::File::FileException& ex ) {
		ex.UpdateStackTrace( GET_CONTEXT() );
		throw;
	}

	int number_of_animations = JSONParser::animations::GetAnimationNumbers();

	for ( int i = 0 ; i<number_of_animations ; i++ ) {
		JSONParser::animations::AnimationElementsFields animation_characteristics = JSONParser::animations::GetAnimationElementsFields( i );
		std::string animation_name = animation_characteristics.name;

		animations.at( animation_name )->SetFrameRate( animation_characteristics.frame_number );
		animations.at( animation_name )->SetAnimationFrameNUmber( animation_characteristics.frame_to_load );

		for ( int j = 0 ; j<animation_characteristics.frame_to_load ; j++ ) {
			Texture* texture = texture_manager->GetTextureByName( animation_characteristics.path + "frame" + std::to_string(j) + ".png" );
			animations.at(animation_name)->AddFrameTexture( texture );
		}
	}

}

void Player::Draw( SDL_Renderer* renderer ) {

	float w = current_animation->GetCurrentFrameTextureWidth();
	float h = current_animation->GetCurrentFrameTextureHeight();

	player_rect.w = w * scale;
	player_rect.h = h * scale;

	player_rect.x = pos_x * scale - player_rect.w / 2;
	player_rect.y = pos_y * scale - player_rect.h / 2;

	SDL_RenderTexture(renderer, current_animation->GetCurrentFrameTexture()->GetTexture(), nullptr, &player_rect);

}

void Player::Update(float delta_time ) {
    UpdatePhysics( delta_time );
	UpdateAnimationFrame() ;
}

void Player::UpdatePhysics(float dt)
{
    // =====================================================
    // WALL CLING MODE
    // =====================================================
    if ((attached_to_wall_left || attached_to_wall_right))
    {

        if ( is_jumping ) {
            switch( this->direction ) {
                case Player::FacingDirection::WEST:
                    velocity_y += gravity * dt;
                    pos_y += velocity_y * dt;

                    if (velocity_y < 0.0f)
                    {
                        is_jumping = true;
                        is_falling = false;

                        if (state != PlayerState::JUMP) {
                            SetPlayerDirection(FacingDirection::EAST);
                            SetPlayerState(PlayerState::JUMP);
                        }
                    }
                    else
                    {
                        is_jumping = false;
                        is_falling = true;

                        if (state != PlayerState::FALLING) {
                            SetPlayerState(PlayerState::FALLING);
                        }
                    }

                    break;

                case Player::FacingDirection::EAST:
                    velocity_y += gravity * dt;
                    pos_y += velocity_y * dt;

                    if (velocity_y < 0.0f)
                    {
                        is_jumping = true;
                        is_falling = false;

                        if (state != PlayerState::JUMP) {
                            SetPlayerDirection(FacingDirection::WEST);
                            SetPlayerState(PlayerState::JUMP);
                        }
                    }
                    else
                    {
                        is_jumping = false;
                        is_falling = true;

                        if (state != PlayerState::FALLING) {
                            SetPlayerState(PlayerState::FALLING);
                        }
                    }

                    break;
            }

            attached_to_wall_left = false;
            attached_to_wall_right = false;

        } else {
            velocity_y = 0;
            is_jumping = false;
            is_falling = false;
        }
        return;
    }

    // =====================================================
    // NORMAL AIR PHYSICS
    // =====================================================
    if (!on_ground)
    {
        velocity_y += gravity * dt;
        pos_y += velocity_y * dt;

        if (velocity_y < 0.0f)
        {
            is_jumping = true;
            is_falling = false;

            if (state != PlayerState::JUMP)
                SetPlayerState(PlayerState::JUMP);
        }
        else
        {
            is_jumping = false;
            is_falling = true;

            if (state != PlayerState::FALLING)
                SetPlayerState(PlayerState::FALLING);
        }
    }
    else
    {
        velocity_y = 0.0f;
        is_jumping = false;
        is_falling = false;
    }
}

void Player::UpdateAnimationFrame()
{
    Animation* crt = current_animation;
    Animation* toSet = nullptr;

    switch (state)
    {
        case PlayerState::RUN:
        {
            if (direction == FacingDirection::WEST)
                toSet = animations.at("RUN_LEFT");
            else
                toSet = animations.at("RUN_RIGHT");
            break;
        }

        case PlayerState::IDLE:
        {
            if (direction == FacingDirection::WEST)
                toSet = animations.at("IDLE_LEFT");
            else
                toSet = animations.at("IDLE_RIGHT");
            break;
        }

        case PlayerState::JUMP:
        {
            if (direction == FacingDirection::WEST)
                toSet = animations.at("JUMP_LEFT");
            else
                toSet = animations.at("JUMP_RIGHT");
            break;
        }

        case PlayerState::FALLING:
        {
            if (direction == FacingDirection::WEST)
                toSet = animations.at("FALL_LEFT");
            else
                toSet = animations.at("FALL_RIGHT");
            break;
        }
    }

    if (crt != toSet)
        current_animation = toSet;

    current_animation->Update();
}

void Player::Move(FacingDirection dir, float dt)
{
    const float distance = speed * dt;

    bool is_moving = false;

    if (dir == FacingDirection::WEST)
    {
        if (!attached_to_wall_left)
        {
            pos_x -= distance;
            is_moving = true;
        }

        attached_to_wall_right = false;
        SetPlayerDirection(FacingDirection::WEST);
    }
    else if (dir == FacingDirection::EAST)
    {
        if (!attached_to_wall_right)
        {
            pos_x += distance;
            is_moving = true;
        }

        attached_to_wall_left = false;
        SetPlayerDirection(FacingDirection::EAST);
    }

    if (on_ground)
    {
        if (is_moving)
        {
            if (state != PlayerState::RUN)
                SetPlayerState(PlayerState::RUN);
        }
        else
        {
            if (state != PlayerState::IDLE)
                SetPlayerState(PlayerState::IDLE);
        }
    }
}

void Player::Resize() {

	try {
		this-> scale = JSONParser::graphics::GetScale();
	} catch ( HerionException::File::FileMalformedException& ex ) {
		ex.UpdateStackTrace( GET_CONTEXT() );
		throw;
	}

}

void Player::Spawn(const int spawn_x, const int spawn_y) {
	this->pos_x = spawn_x;
	this->pos_y = spawn_y;

}
void Player::Jump()
{
    // WALL JUMP
    if ((attached_to_wall_left || attached_to_wall_right))
    {
        velocity_y = jump_force;

        on_ground = false;
        is_jumping = true;
        is_falling = false;

        return;
    }



    // NORMAL JUMP
    if (on_ground)
    {
        velocity_y = jump_force;

        on_ground = false;
        is_jumping = true;
        is_falling = false;
    }

}

[[nodiscard]] bool Player::IsJumping() const {
	return is_jumping;
}

[[nodiscard]] bool Player::IsFalling() const {
	return is_falling;
}

[[nodiscard]] bool Player::OnGround() const {
	return on_ground;
}

void Player::SetOnGround(bool on_ground) {
	this->on_ground = on_ground;
}

float Player::GetVelocityY() const {
    return this->velocity_y;
}

void Player::SetPositionY(float y) {
    this->pos_y = y;
}

void Player::SetVelocityY(float y) {
    this->velocity_y = y;
}

float& Player::GetPosX() { return pos_x; }
float& Player::GetPosY() { return pos_y; }

float& Player::GetVelocityX() { return velocity_x; }
float& Player::GetVelocityY() { return velocity_y; }

void Player::SetAttachedToWallLeft( bool attached ) {
    this->attached_to_wall_left = attached;
}

void Player::SetAttachedToWallRight( bool attached ) {
    this->attached_to_wall_right = attached;
}

void Player::reset() {
    this->state = PlayerState::IDLE;
	this->direction = FacingDirection::EAST;



	this->velocity_x = 0.0f;
	this->speed = 500;

	this->player_rect.w = 30;
	this->player_rect.h = 60;

	this->player_rect = {pos_x, pos_y, pos_x, pos_y};

	this->fixed_pos_x = this->pos_x;
	this->fixed_pos_y = this->pos_y;

	this->scale = JSONParser::graphics::GetScale();
	this->velocity_y = 0;
}
