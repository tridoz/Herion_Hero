//
// Created by david on 21/11/2025.
//

#include "ButtonsFunctions.hpp"

#include "JSONParser.hpp"

Player* ButtonsFunctions::player = nullptr;

void ButtonsFunctions::SetPlayer( Player* setter_player ) {
    player = setter_player;
}

//CHANGE GAMEMODE
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
void ButtonsFunctions::ReturnPreviousState() {
    player->SetGameMode( player->GetPreviousGameMode() );
}

//GRAPHICS SETTINGS
void ButtonsFunctions::IncreaseResolution() {
    JSONParser::graphics::IncreaseResolution();
}
void ButtonsFunctions::DecreaseResolution() {
    JSONParser::graphics::DecreaseResolution();
}
void ButtonsFunctions::ChangeWindowMode() {

}
void ButtonsFunctions::IncreaseFrameLimit() {

}
void ButtonsFunctions::DecreaseFrameLimit() {

}
void ButtonsFunctions::IncreaseBrightness() {

}
void ButtonsFunctions::DecreaseBrightness() {

}
