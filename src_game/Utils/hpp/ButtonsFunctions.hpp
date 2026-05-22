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
    /**
     * @brief Set the Player::GameMode to IN_GAME
     */
    static void StartGame();

    /**
     * @brief Unimplemented
     */
    static void StartNewGame();

    /**
     * @brief Set the Player::GameMode to EXIT
     */
    static void EndGame();

    /**
     * @brief Set the Player::GameMode to MAIN_MENU
     */
    static void OpenMainMenu();

    /**
     * @brief Set the Player::GameMode to SETTINGS_MENU
     */
    static void OpenGeneralSettingsMenu();

    static void OpenGraphicsSettingsMenu();

    static void OpenAudioSettingsMenu();

    /**
     * @brief Set the Player::Gamemode to LEVEL_EDITOR
     */
    static void OpenEditorMenu();

    /**
     * @brief Set the player::GameMode to TEXTURE_SELECTIONS
     */
    static void OpenTextureSelectionMenu();

    /**
     * @brief Set the Player::Gamemode to LEVEL_EDITOR
     */
    static void OpenLevelEditor();

    /**
     * @brief Set the Player::GameMode to ANIMATION_EDITOR
     */
    static void OpenAnimationEditor();


    /**
     * @brief Set the player::GameMode to Player::GetPreviousGameMode()
     */
    static void ReturnPreviousState();


    //GRAPHICS SETTINGS
    /**
     * @brief Call JSONParser::graphics::IncreaseResolution();
     */
    static void IncreaseResolution();

    /**
     * @brief Call JSONParser::graphics::DecreaseResolution();
     */
    static void DecreaseResolution();

    /**
     * @brief Unimplement
     */
    static void ChangeWindowMode();

    /**
     * @brief Call JSONParser::graphics::IncreaseFPSLimit();
     */
    static void IncreaseFrameLimit();

    /**
     * @brief Call JSONParser::graphics::DecreaseFPSLimit();
     */
    static void DecreaseFrameLimit();

    /**
     * Unimplemented
     */
    static void IncreaseBrightness();

    /**
     * Unimplemented
     */
    static void DecreaseBrightness();

    //AUDIO SETTINGS

    /**
     * Unimplemented
     */
    static void IncreaseGeneralAudio();

    /**
     * Unimplemented
     */
    static void DecreaseGeneralAudio();

    /**
     * Unimplemented
     */
    static void IncreaseMusicVolume();

    /**
     * Unimplemented
     */
    static void DecreaseMusicVolume();

    /**
     * Unimplemented
     */
    static void IncreaseEffectsVolume();

    /**
     * Unimplemented
     */
    static void DecreaseEffectsVolume();

    /**
     * Unimplemented
     */
    static void ToggleMute();

    /**
     * Unimplemented
     */
    static void SelectMusicTrack();

    //KEYMAPPING

    /**
     * Unimplemented
     */
    static void ResetKeybinds();

    /**
     * Unimplemented
     */
    static void ChangeKey();

    //GAME

    /**
     * Unimplemented
     */
    static void IncreaseDifficulty();

    /**
     * Unimplemented
     */
    static void DecreaseDifficulty();

    /**
     * Unimplemented
     */
    static void ChangeGameMode();

    /**
     * Unimplemented
     */
    static void ToggleTutorial();

    //INTERFACE

    /**
     * Unimplemented
     */
    static void ToggleHUD();

    /**
     * Unimplemented
     */
    static void ChangeTheme();

    //SAVE

    /**
     * Unimplemented
     */
    static void ToggleAutoSave();

    /**
     * Unimplemented
     */
    static void IncreaseAutoSaveTime();

    /**
     * Unimplemented
     */
    static void DecreaseAutoSaveTime();

    /**
     * Unimplemented
     */
    static void ToggleSaveCloud();

    /**
     * @brief Set the player to do the operations
     * @param player Pointer to the Player
     */
    static void SetPlayer( Player* player );

    /**
     * @brief Set the TextureManager to do the operations
     * @param texture_manager Pointer to the Texturemanager
     */
    static void SetTextureManager( TextureManager* texture_manager );
};


#endif //HERION_HERO_BUTTONSFUNCTIONS_HPP