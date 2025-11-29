//
// Created by trida on 11/19/25.
//

#include "../hpp/Player.hpp"


Player::Player() {
	this->mode = MAIN_MENU;
	this->state = IDLE;
}

Player::~Player() {
	this->mode = MAIN_MENU;
	this->state = IDLE;
}

Player::GameMode Player::GetGameMode() const {
	return mode;
}

Player::PlayerState Player::GetPlayerState() const {
	return state;
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
