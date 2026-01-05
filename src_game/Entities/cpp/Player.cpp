//
// Created by trida on 11/19/25.
//

#include "../hpp/Player.hpp"

#include "../../Textures/hpp/TextureManager.hpp"
#include "../../Utils/hpp/JSONParser.hpp"


Player::Player() {

	this->mode = GameMode::MAIN_MENU;
	this->state = PlayerState::IDLE;
	this->direction = FacingDirection::SOUTH;

	this->pos_x = 200;
	this->pos_y = 200;

	this->next_x = pos_x;
	this->next_y = pos_y;

	this->speed = 1000;

	this->player_rect = {pos_x, pos_y, pos_x, pos_y};

	this->fixed_pos_x = this->pos_x;
	this->fixed_pos_y = this->pos_y;

	this->scale = JSONParser::graphics::GetScale();

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

	if ( !animations.contains( str_state + str_direction ) ) {
		THROW_FILE_NOT_FOUND( str_state + str_direction );
	}

	current_animation = animations.at( str_state + str_direction );

}

void Player::SetTextureManager( TextureManager *new_texture_manager ) {
	this->texture_manager = new_texture_manager;
}

void Player::LoadAnimation( const std::string &filepath, const std::string &animation_name ) {

	std::ifstream animation_cfg_file;

	try {
		FileOpener::OpenFileInput( animation_cfg_file, "../" + filepath );
	} catch ( HerionException::File::FileException& ex ) {
		ex.UpdateStackTrace( GET_CONTEXT() );
		throw;
	}


	std::string line;
	try {
		std::getline( animation_cfg_file, line );
		int frame_number = std::stoi( line );

		if ( !animations.contains( animation_name ) ) {
			THROW_FILE_NOT_FOUND( animation_name );
		}

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

		if ( !animations.contains( animation_name ) ) {
			THROW_FILE_NOT_FOUND( animation_name );
		}

		animations.at( animation_name )->AddFrameTexture( animation_texture );
	}

}

void Player::Draw( SDL_Renderer* renderer ) {

	float w = current_animation->GetCurrentFrameTextureWidth();
	float h = current_animation->GetCurrentFrameTextureHeight();

	player_rect.w = w * scale;
	player_rect.h = h * scale;

	player_rect.x = pos_x * scale - player_rect.w / 2;
	player_rect.y = pos_y * scale - player_rect.h / 2;

	SDL_RenderTexture( renderer, current_animation->GetCurrentFrameTexture()->GetTexture(), nullptr, &player_rect );
}

void Player::Update( SDL_Renderer* renderer ) {

	double distance_x = std::abs( pos_x - next_x );
	double distance_y = std::abs( pos_y - next_y );


	double distance = std::sqrt( distance_x * distance_x + distance_y * distance_y );

	double FrameRate;
	try {
		FrameRate = JSONParser::graphics::GetFrameRate();
	} catch ( HerionException::File::FileMalformedException& ex) {
		ex.UpdateStackTrace( GET_CONTEXT() );
		throw;
	}

	const double deltaTime = 1.0 / FrameRate;

	if ( distance >= this->speed * deltaTime ) {

		this->state = PlayerState::RUN;

		const double dx = speed * deltaTime * std::cos(movement_angle);
		const double dy = speed * deltaTime * std::sin(movement_angle);

		pos_x += dx;
		pos_y += dy;

	} else {

		pos_x = next_x;
		pos_y = next_y;

		state = PlayerState::IDLE;
	}

	UpdateAnimationFrame( renderer ) ;
}

void Player::UpdateAnimationFrame( SDL_Renderer* renderer ) {
	Animation* crt = current_animation;

	Animation* toSet = nullptr;

	if ( state == PlayerState::RUN ) {
		switch ( direction ) {
			case FacingDirection::NORTH:
				toSet = animations.at( "RUN_UP" );
			break;

			case FacingDirection::WEST:
				toSet = animations.at( "RUN_LEFT" );
			break;

			case FacingDirection::SOUTH:
				toSet = animations.at( "RUN_DOWN" );
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
			case FacingDirection::NORTH:
				toSet = animations.at( "IDLE_UP" );
				break;

			case FacingDirection::WEST:
				toSet = animations.at( "IDLE_LEFT" );
				break;

			case FacingDirection::SOUTH:
				toSet = animations.at( "IDLE_DOWN" );
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

void Player::Move( float x, float y ) {

	this-> next_x = x / scale;
	this-> next_y = y / scale;

	const double distanceX = next_x - pos_x;
	const double distanceY = next_y - pos_y;

	this->movement_angle = atan2( distanceY, distanceX );

	const float degree = this->movement_angle * 180 / M_PI;


	if ( degree > -45 && degree <= 45 ) {
		this->direction = FacingDirection::EAST;
	}else if ( degree > 45 && degree <= 135) {
		this->direction = FacingDirection::SOUTH;
	}else if ( degree > -135 && degree <= -45) {
		this->direction = FacingDirection::NORTH;
	}else {
		this->direction = FacingDirection::WEST;
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





