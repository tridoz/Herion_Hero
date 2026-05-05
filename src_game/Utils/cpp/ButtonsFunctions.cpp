//
// Created by david on 21/11/2025.
//

#include "../hpp/ButtonsFunctions.hpp"

#include "../hpp/JSONParser.hpp"

Player* ButtonsFunctions::player = nullptr;

void ButtonsFunctions::SetPlayer( Player* setter_player ) {
    player = setter_player;
}
void ButtonsFunctions::SetTextureManager( TextureManager* setter_texture_manager ) {
    texture_manager = setter_texture_manager;
}
void ButtonsFunctions::SetTexture( Texture* setter_texture ) {
    texture = setter_texture;
}
Texture* ButtonsFunctions::GetTexture() {
    return texture;
}

//EDITOR ACTION


//CHANGE GAMEMODE
void ButtonsFunctions::StartGame() {
    player->SetGameMode( Player::GameMode::IN_GAME );
}
void ButtonsFunctions::StartNewGame() {

}
void ButtonsFunctions::EndGame() {
    player->SetGameMode( Player::GameMode::EXIT );
}
void ButtonsFunctions::OpenMainMenu() {
    player->SetGameMode( Player::GameMode::MAIN_MENU );
}
void ButtonsFunctions::OpenEditorMenu() {
    player->SetGameMode( Player::GameMode::EDITOR_MENU );
}
void ButtonsFunctions::OpenSettings() {
    player->SetGameMode( Player::GameMode::SETTINGS_MENU );
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
    JSONParser::graphics::IncreaseFPSLimit();
}
void ButtonsFunctions::DecreaseFrameLimit() {
    JSONParser::graphics::DecreaseFPSLimit();
}
void ButtonsFunctions::IncreaseBrightness() {

}
void ButtonsFunctions::DecreaseBrightness() {

}
