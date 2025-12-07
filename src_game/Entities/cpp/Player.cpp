//
// Created by trida on 11/19/25.
//

#include "../hpp/Player.hpp"

#include "../../Textures/hpp/TextureManager.hpp"
#include "../../Utils/hpp/JSONParser.hpp"


Player::Player() {

	this->mode = GameMode::MAIN_MENU;
	this->state = PlayerState::IDLE;

	this->pos_x = 200;
	this->pos_y = 200;

	this->fixed_pos_x = this->pos_x;
	this->fixed_pos_y = this->pos_y;

	animations.emplace( "IDLE_DOWN", new Animation() );
	animations.emplace( "IDLE_LEFT", new Animation() );
	animations.emplace( "IDLE_UP", new Animation() );
	animations.emplace( "IDLE_RIGHT", new Animation() );

	animations.emplace("RUN_DOWN", new Animation() );
	animations.emplace("RUN_LEFT", new Animation() );
	animations.emplace("RUN_UP", new Animation() );
	animations.emplace("RUN_RIGHT", new Animation() );

	current_animation = animations.at("IDLE_DOWN");

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
	this->previousState = new_player_state;
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
		case PlayerState::IDLE:
			str_state = "IDLE_";
			break;

		case PlayerState::RUN:
			str_state = "RUN_";
			break;
	}

	switch ( new_direction ) {
		case FacingDirection::NORTH:
			str_direction = "UP";
			break;

		case FacingDirection::WEST:
			str_direction = "LEFT";
			break;

		case FacingDirection::SOUTH:
			str_direction = "DOWN";
			break;

		case FacingDirection::EAST:
			str_direction = "RIGHT";
			break;
	}

	current_animation = animations.at( str_state + str_direction );

}


void Player::SetTextureManager( TextureManager *new_texture_manager ) {
	this->texture_manager = new_texture_manager;
}

void Player::LoadAnimation( const std::string &filepath, const std::string &animation_name ) {

	std::ifstream animation_cfg_file( "../" + filepath );
	if ( !animation_cfg_file.is_open() ) {
		Logger::LogErr(
			std::time(nullptr),
			"OPENING",
			"Player",
			"LoadAnimation",
			"Error while opening file [" + filepath + "]"  + strerror( errno )
			);
		return;
	}

	std::string line;
	try {
		std::getline( animation_cfg_file, line );
		int frame_number = std::stoi( line );

		animations.at( animation_name )->SetAnimationFrameNUmber( frame_number );
		animations.at( animation_name )->SetFrameRate( frame_number );

	} catch ( std::invalid_argument ) {
		Logger::LogErr(
			std::time(nullptr),
			"PARSING",
			"Player",
			"LoadAnimation",
			"File " + filepath + " is malformed"
			);
		return;

	}

	while ( std::getline( animation_cfg_file, line ) ) {
		Texture* animation_texture = texture_manager->GetTexture( line );
		animations.at( animation_name )->AddFrameTexture( animation_texture );
		float w, h;
		SDL_GetTextureSize( animation_texture->GetTexture(), &w, &h );
		SDL_FRect* animation_rect = new SDL_FRect;

		pos_x = fixed_pos_x;
		pos_y = fixed_pos_y - h;

		animation_rect->x = pos_x;
		animation_rect->y = pos_y;
		animation_rect->w = w;
		animation_rect->h = h;
		animations.at( animation_name )->AddFrameRect( animation_rect );
	}

}

void Player::Draw( SDL_Renderer* renderer ) const {
	SDL_RenderTexture( renderer, current_animation->GetCurrentFrameTexture()->GetTexture(), nullptr, current_animation->GetCurrentFrameRect() );
}

void Player::Update() const {
	current_animation->Update();
}



