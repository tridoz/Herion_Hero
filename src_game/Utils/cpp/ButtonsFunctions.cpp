//
// Created by david on 21/11/2025.
//

#include "../hpp/ButtonsFunctions.hpp"

#include "../hpp/JSONParser.hpp"

Player* ButtonsFunctions::player = nullptr;
TextureManager* ButtonsFunctions::texture_manager = nullptr;
Texture* ButtonsFunctions::texture = nullptr;

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


//CHANGE GAME MODE
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
void ButtonsFunctions::OpenLevelEditor() {
    player->SetGameMode( Player::GameMode::LEVEL_EDITOR );
}
void ButtonsFunctions::OpenAnimationEditor() {
    player->SetGameMode( Player::GameMode::ANIMATION_EDITOR );
}
void ButtonsFunctions::OpenEditorMenu() {
    player->SetGameMode( Player::GameMode::EDITOR_MENU );
}
void ButtonsFunctions::OpenGeneralSettingsMenu() {
    player->SetGameMode( Player::GameMode::GENERAL_SETTINGS_MENU );
}
void ButtonsFunctions::OpenGraphicsSettingsMenu() {
    player->SetGameMode( Player::GameMode::GRAPHICS_SETTINGS_MENU );
}
void ButtonsFunctions::OpenAudioSettingsMenu() {
    player->SetGameMode( Player::GameMode::AUDIO_SETTINGS_MENU );
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

//AUDIO SETTINGS
void ButtonsFunctions::IncreaseMasterVolume() {
    JSONParser::audio::IncreaseMasterVolume();
}
void ButtonsFunctions::DecreaseMasterVolume() {
    JSONParser::audio::DecreaseMasterVolume();
}