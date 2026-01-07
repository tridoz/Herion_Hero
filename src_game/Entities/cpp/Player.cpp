//
// Created by trida on 11/19/25.
//

#include "../hpp/Player.hpp"

#include "../../Textures/hpp/TextureManager.hpp"
#include "../../Utils/hpp/JSONParser.hpp"


Player::Player() {

	this->mode = GameMode::MAIN_MENU;
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
			Texture* texture = texture_manager->GetTexture( animation_characteristics.path + "frame" + std::to_string(j) + ".png" );
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

void Player::Update( SDL_Renderer* renderer ) {

	UpdateAnimationFrame( renderer ) ;
}

void Player::UpdateAnimationFrame( SDL_Renderer* renderer ) {
	Animation* crt = current_animation;

	Animation* toSet = nullptr;

	if ( state == PlayerState::RUN ) {
		switch ( direction ) {


			case FacingDirection::WEST:
				toSet = animations.at( "RUN_LEFT" );
			break;

			case FacingDirection::EAST:
				toSet = animations.at( "RUN_RIGHT" );
				break;

		}


		if ( crt != toSet ) {
			current_animation = toSet;
		}

		current_animation->Update();

	} else if ( state == PlayerState::IDLE ) {
		switch ( direction ) {

			case FacingDirection::WEST:
				toSet = animations.at( "IDLE_LEFT" );
				break;

			case FacingDirection::EAST:
				toSet = animations.at( "IDLE_RIGHT" );
				break;

		}

		if ( crt != toSet ) {
			current_animation = toSet;
		}

		current_animation->Update();

	}
}

void Player::Move(FacingDirection direction, float delta_time) {

	const float distance = speed * delta_time;

	bool is_moving = false;

	if (direction == FacingDirection::WEST) {
		pos_x -= distance;
		is_moving = true;

		if (this->direction != FacingDirection::WEST)
			SetPlayerDirection(FacingDirection::WEST);
	}

	else if (direction == FacingDirection::EAST) {
		pos_x += distance;
		is_moving = true;

		if (this->direction != FacingDirection::EAST)
			SetPlayerDirection(FacingDirection::EAST);
	}

	if (is_moving) {
		if (state != PlayerState::RUN)
			SetPlayerState(PlayerState::RUN);
	} else {
		if (state != PlayerState::IDLE)
			SetPlayerState(PlayerState::IDLE);
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





