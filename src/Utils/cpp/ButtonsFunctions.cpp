//
// Created by david on 21/11/2025.
//

#include "../hpp/ButtonsFunctions.hpp"
#include "../../Engine/hpp/Engine.hpp"

#include "../hpp/JSONParser.hpp"

Player* ButtonsFunctions::player = nullptr;
TextureManager* ButtonsFunctions::texture_manager = nullptr;
Texture* ButtonsFunctions::texture = nullptr;

auto ButtonsFunctions::SetPlayer(Player* setter_player) -> void {
    player = setter_player;
}
auto ButtonsFunctions::SetTextureManager(TextureManager* setter_texture_manager) -> void {
    texture_manager = setter_texture_manager;
}
auto ButtonsFunctions::SetTexture(Texture* setter_texture) -> void {
    texture = setter_texture;
}
auto ButtonsFunctions::GetTexture() -> Texture* {
    return texture;
}

// CHANGE GAME MODE
auto ButtonsFunctions::StartGame() -> void {
    Engine::SetGameState(Engine::GameState::IN_GAME);
}
auto ButtonsFunctions::StartNewGame() -> void{
}

auto ButtonsFunctions::EndGame() -> void {
    Engine::SetGameState(Engine::GameState::EXIT);
}
auto ButtonsFunctions::OpenMainMenu() -> void {
    Engine::SetGameState(Engine::GameState::MAIN_MENU);
}
auto ButtonsFunctions::OpenLevelEditor() -> void {
    Engine::SetGameState(Engine::GameState::LEVEL_EDITOR);
}
auto ButtonsFunctions::OpenAnimationEditor() -> void {
    Engine::SetGameState(Engine::GameState::ANIMATION_EDITOR);
}
auto ButtonsFunctions::OpenEditorMenu() -> void {
    Engine::SetGameState(Engine::GameState::EDITOR_MENU);
}
auto ButtonsFunctions::OpenGeneralSettingsMenu() -> void {
    Engine::SetGameState(Engine::GameState::GENERAL_SETTINGS_MENU);
}
auto ButtonsFunctions::OpenGraphicsSettingsMenu() -> void {
    Engine::SetGameState(Engine::GameState::GRAPHICS_SETTINGS_MENU);
}
auto ButtonsFunctions::OpenAudioSettingsMenu() -> void {
    Engine::SetGameState(Engine::GameState::AUDIO_SETTINGS_MENU);
}
auto ButtonsFunctions::ReturnPreviousState() -> void {
    Engine::SetGameState(Engine::GetPreviousState());
}

// GRAPHICS SETTINGS
auto ButtonsFunctions::IncreaseResolution() -> void {
    JSONParser::graphics::IncreaseResolution();
}
auto ButtonsFunctions::DecreaseResolution() -> void {
    JSONParser::graphics::DecreaseResolution();
}
auto ButtonsFunctions::ChangeWindowMode() -> void {
}
auto ButtonsFunctions::IncreaseFrameLimit() -> void {
    JSONParser::graphics::IncreaseFPSLimit();
}
auto ButtonsFunctions::DecreaseFrameLimit() -> void {
    JSONParser::graphics::DecreaseFPSLimit();
}
auto ButtonsFunctions::IncreaseBrightness() -> void {
}
auto ButtonsFunctions::DecreaseBrightness() -> void {
}

// AUDIO SETTINGS
auto ButtonsFunctions::SetMasterVolume(int volume) -> void {
    JSONParser::audio::SetMasterVolume(volume);
}
auto ButtonsFunctions::IncreaseMasterVolume() -> void {
    JSONParser::audio::IncreaseMasterVolume();
}
auto ButtonsFunctions::DecreaseMasterVolume() -> void {
    JSONParser::audio::DecreaseMasterVolume();
}

auto ButtonsFunctions::IncreaseMusicVolume() -> void {
    JSONParser::audio::IncreaseMusicVolume();
}
auto ButtonsFunctions::DecreaseMusicVolume() -> void {
    JSONParser::audio::DecreaseMusicVolume();
}

auto ButtonsFunctions::IncreaseSFXVolume() -> void {
    JSONParser::audio::IncreaseSFXVolume();
}
auto ButtonsFunctions::DecreaseSFXVolume() -> void {
    JSONParser::audio::DecreaseSFXVolume();
}
