//
// Created by david on 21/11/2025.
//

#ifndef HERION_HERO_BUTTONSFUNCTIONS_HPP
#define HERION_HERO_BUTTONSFUNCTIONS_HPP

#include "../../Entities/hpp/Player.hpp"

class ButtonsFunctions {

  private:
    static Player* player;
    static TextureManager* texture_manager;
    static Texture* texture;

    static auto SetTexture(Texture*) -> void;
    static auto GetTexture() -> Texture*;

  public:
    static auto StartGame() -> void;
    static auto StartNewGame() -> void;
    static auto EndGame() -> void;
    static auto OpenMainMenu() -> void;
    static auto OpenGeneralSettingsMenu() -> void;
    static auto OpenGraphicsSettingsMenu() -> void;
    static auto OpenAudioSettingsMenu() -> void;
    static auto OpenEditorMenu() -> void;
    static auto OpenTextureSelectionMenu() -> void;
    static auto OpenLevelEditor() -> void;
    static auto OpenAnimationEditor() -> void;
    static auto ReturnPreviousState() -> void;
    static auto IncreaseResolution() -> void;
    static auto DecreaseResolution() -> void;
    static auto ChangeWindowMode() -> void;
    static auto IncreaseFrameLimit() -> void;
    static auto DecreaseFrameLimit() -> void;
    static auto IncreaseBrightness() -> void;
    static auto DecreaseBrightness() -> void;
    static auto SetMasterVolume(int) -> void;
    static auto IncreaseMasterVolume() -> void;
    static auto DecreaseMasterVolume() -> void;
    static auto SetMusicVolume(int) -> void;
    static auto IncreaseMusicVolume() -> void;
    static auto DecreaseMusicVolume() -> void;
    static auto SetSFXVolume(int) -> void;
    static auto IncreaseSFXVolume() -> void;
    static auto DecreaseSFXVolume() -> void;
    static auto ToggleMute() -> void;
    static auto SelectMusicTrack() -> void;
    static auto ResetKeybinds() -> void;
    static auto ChangeKey() -> void;
    static auto IncreaseDifficulty() -> void;
    static auto DecreaseDifficulty() -> void;
    static auto ChangeGameMode() -> void;
    static auto ToggleTutorial() -> void;
    static auto ToggleHUD() -> void;
    static auto ChangeTheme() -> void;
    static auto ToggleAutoSave() -> void;
    static auto IncreaseAutoSaveTime() -> void;
    static auto DecreaseAutoSaveTime() -> void;
    static auto ToggleSaveCloud() -> void;
    static auto SetPlayer(Player*) -> void;
    static auto SetTextureManager(TextureManager*) -> void;
};

#endif // HERION_HERO_BUTTONSFUNCTIONS_HPP
