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
