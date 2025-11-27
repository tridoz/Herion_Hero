//
// Created by trida on 11/19/25.
//

#include "Player.hpp"


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

void Player::SetPlayerState( PlayerState state ) {
	this->previousState = state;
	this->state = state;
}

void Player::SetGameMode( GameMode mode ) {
	this->previousGameMode = this->mode;
	this->mode = mode;
}
