//
// Created by david on 21/11/2025.
//

#include "ButtonsFunctions.hpp"

Player* ButtonsFunctions::player = nullptr;

void ButtonsFunctions::StartGame() {
    player->SetGameMode( Player::IN_GAME );
}

void ButtonsFunctions::EndGame() {
    player->SetGameMode( Player::EXIT );
}

void ButtonsFunctions::OpenMainMenu() {
    player->SetGameMode( Player::MAIN_MENU );
}

void ButtonsFunctions::OpenSettings() {
    player->SetGameMode( Player::SETTINGS_MENU );
}

void ButtonsFunctions::CloseSettings() {
    player->SetGameMode( player->GetPreviousGameMode() );
}

void ButtonsFunctions::SetPlayer( Player* setter_player ) {
    player = setter_player;
}
