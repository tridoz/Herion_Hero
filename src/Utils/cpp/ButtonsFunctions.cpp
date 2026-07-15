//
// Created by david on 21/11/2025.
//

#include "../hpp/ButtonsFunctions.hpp"
#include "../../Engine/hpp/Engine.hpp"

#include "../hpp/JSONParser.hpp"

Player* ButtonsFunctions::player = nullptr;
TextureManager* ButtonsFunctions::texture_manager = nullptr;
Texture* ButtonsFunctions::texture = nullptr;

void ButtonsFunctions::SetPlayer(Player* setter_player) {
    player = setter_player;
}
void ButtonsFunctions::SetTextureManager(TextureManager* setter_texture_manager) {
    texture_manager = setter_texture_manager;
}
void ButtonsFunctions::SetTexture(Texture* setter_texture) {
    texture = setter_texture;
}
Texture* ButtonsFunctions::GetTexture() {
    return texture;
}

// CHANGE GAME MODE
void ButtonsFunctions::StartGame() {
    Engine::SetGameState(Engine::GameState::IN_GAME);
}
void ButtonsFunctions::StartNewGame() {
}
void ButtonsFunctions::EndGame() {
    Engine::SetGameState(Engine::GameState::EXIT);
}
void ButtonsFunctions::OpenMainMenu() {
    Engine::SetGameState(Engine::GameState::MAIN_MENU);
}
void ButtonsFunctions::OpenLevelEditor() {
    Engine::SetGameState(Engine::GameState::LEVEL_EDITOR);
}
void ButtonsFunctions::OpenAnimationEditor() {
    Engine::SetGameState(Engine::GameState::ANIMATION_EDITOR);
}
void ButtonsFunctions::OpenEditorMenu() {
    Engine::SetGameState(Engine::GameState::EDITOR_MENU);
}
void ButtonsFunctions::OpenGeneralSettingsMenu() {
    Engine::SetGameState(Engine::GameState::GENERAL_SETTINGS_MENU);
}
void ButtonsFunctions::OpenGraphicsSettingsMenu() {
    Engine::SetGameState(Engine::GameState::GRAPHICS_SETTINGS_MENU);
}
void ButtonsFunctions::OpenAudioSettingsMenu() {
    Engine::SetGameState(Engine::GameState::AUDIO_SETTINGS_MENU);
}
void ButtonsFunctions::ReturnPreviousState() {
    // Engine::SetGameState(Engine::GetPreviousGameState());
}

// GRAPHICS SETTINGS
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

// AUDIO SETTINGS
void ButtonsFunctions::SetMasterVolume(int volume) {
    JSONParser::audio::SetMasterVolume(volume);
}
void ButtonsFunctions::IncreaseMasterVolume() {
    JSONParser::audio::IncreaseMasterVolume();
}
void ButtonsFunctions::DecreaseMasterVolume() {
    JSONParser::audio::DecreaseMasterVolume();
}

void ButtonsFunctions::IncreaseMusicVolume() {
    JSONParser::audio::IncreaseMusicVolume();
}
void ButtonsFunctions::DecreaseMusicVolume() {
    JSONParser::audio::DecreaseMusicVolume();
}

void ButtonsFunctions::IncreaseSFXVolume() {
    JSONParser::audio::IncreaseSFXVolume();
}
void ButtonsFunctions::DecreaseSFXVolume() {
    JSONParser::audio::DecreaseSFXVolume();
}
