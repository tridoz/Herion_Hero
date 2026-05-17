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

    static void SetTexture( Texture* texture );
    static Texture* GetTexture();

public:

    // CHANGE GAMEMODE
    static void StartGame();
    static void StartNewGame();
    static void EndGame();
    static void OpenMainMenu();
    static void OpenSettings();
    static void OpenEditorMenu();
    static void OpenTextureSelectionMenu();
    static void OpenLevelEditor();
    static void OpenAnimationEditor();
    static void CloseSettings();
    static void ReturnPreviousState();

    // EDITOR ACTION
    static void PlaceTexture();
    static void RemoveTexture();
    static void LoadRoom();
    static void LoadTexture();

    //GRAPHICS SETTINGS
    static void IncreaseResolution();
    static void DecreaseResolution();
    static void ChangeWindowMode();
    static void IncreaseFrameLimit();
    static void DecreaseFrameLimit();
    static void IncreaseBrightness();
    static void DecreaseBrightness();

    //AUDIO SETTINGS
    static void IncreaseGeneralAudio();
    static void DecreaseGeneralAudio();
    static void IncreaseMusicVolume();
    static void DecreaseMusicVolume();
    static void IncreaseEffectsVolume();
    static void DecreaseEffectsVolume();
    static void ToggleMute();
    static void SelectMusicTrack();

    //KEYMAPPING
    static void ResetKeybinds();
    static void ChangeKey();

    //GAME
    static void IncreaseDifficulty();
    static void DecreaseDifficulty();
    static void ChangeGameMode();
    static void ToggleTutorial();

    //INTERFACE
    static void ToggleHUD();
    static void ChangeTheme();

    //SAVE
    static void ToggleAutoSave();
    static void IncreaseAutoSaveTime();
    static void DecreaseAutoSaveTime();
    static void ToggleSaveCloud();

    static void SetPlayer( Player* player );
    static void SetTextureManager( TextureManager* texture_manager );
};


#endif //HERION_HERO_BUTTONSFUNCTIONS_HPP