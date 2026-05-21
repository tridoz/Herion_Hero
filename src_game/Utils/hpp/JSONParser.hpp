//
// Created by david on 23/11/2025.
//

#ifndef HERION_HERO_JSONPARSERER_HPP
#define HERION_HERO_JSONPARSERER_HPP

#include "../../../headers_only_dependencies/json.hpp"
#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "FileOpener.hpp"

#include <fstream>

#include "Logger.hpp"

namespace JSONParser {

    namespace audio {
        inline const std::string json_audio_file_path = "../settings/audio.json";

        void IncreaseMasterVolume();
        void DecreaseMasterVolume();

        void IncreaseMusicVolume();
        void DecreaseMusicVolume();

        void IncreaseSFXVolume();
        void DecreaseSFXVolume();

        void ToggleMute();
    }

    namespace controls {

    }

    namespace gameplay {

    }

    namespace graphics {

        static inline const std::vector<int> allowedFPS = {10, 15, 20, 30, 45, 60, 120, 180, 240, 360, 500};
        inline const std::string json_graphics_file_path = "../settings/graphics.json";
        inline bool changed = false;

        /**
         * @brief DataStructure for all the possible resolutions
         */
        inline const std::vector < std::pair <int, int > > resolutions{
            { 640, 360},
            { 854, 480 },
            { 960, 540 },
            { 1280, 720 },
            { 1600, 900 },
            { 1920, 1080 },
            { 2560, 1440 },
            { 3840, 2160 }
        };

        /**
         * @brief DataStructure for all the scale based on the resolution
         */
        inline const std::vector<float> texture_scales{
            0.25,
            0.333,
            0.375,
            0.5,
            0.625,
            0.75,
            1.0,
            1.5
        };

        /**
         * @brief Function to increase the screen resolution
         */
        void IncreaseResolution();

        /**
         * @brief Function to decrease the screen resolution
         */
        void DecreaseResolution();

        /**
         * @brief Function to get the width of the screen
         * @return int
         */
        int GetWidth();

        /**
         * @brief Function to get the height of the screen
         * @return int
         */
        int GetHeight();

        /**
         * @brief Function to get increase the FPS limit
         */
        void IncreaseFPSLimit();

        /**
         * @brief Function to get decrease the FPS limit
         */
        void DecreaseFPSLimit();

        /**
         * @brief Return if the resolution has changed
         * @return bool
         */
        bool Changed();

        /**
         * @return Set the fact that changes have been successfully applied
         */
        void ChangesApplied();

        /**
         * @brief Return the scale for the current resolution
         * @return float
         */
        float GetScale();

        /**
         * @brief Return the current FPS limit
         * @return int
         */
        int GetFrameRate();

    }

    namespace ui {

    }

    namespace menu_configuration {
        inline nlohmann::json config_file;
        inline std::string config_file_path;

        /**
         * @struct RowElementFields
         * @brief Struct to save the Element fields in the Button type menu configuration
         */
        struct RowElementFields {
            std::string type;
            std::string text;
            std::optional<std::string> action;
            std::optional< std::string > return_value;
            std::string id;
        };

        /**
         * @brief Set the .json file to parse
         * @param config_file_path Path to the .json configuration file
         */
        void SetConfigFile( const std::string& config_file_path );

        /**
         * @brief Return the path to the background image
         * @return std::string
         */
        std::string GetBackgroundImagePath();

        /**
         * @brief Return the menu type
         * @return std::string
         */
        std::string GetMenuType();

        std::string GetButtonStyle();

        std::string GetFontStyle();

        float GetCharWidth();

        /**
         * @brief Return the command to execute
         * @return std::string
         */
        std::string GetCmd();

        /**
         * @brief Get the Texture size for the directory row
         * @return int
         */
        int GetDirectoryTextureSize();

        /**
         * @brief Get the Texture size for the file row
         * @return int
         */
        int GetFileTextureSize();

        /**
         * @brief Get the StartY for the Button menu type
         * @return float
         */
        float GetStartY();

        /**
         * @brief Get the ButtonYOffset for the Button menu type
         * @return float
         */
        float GetButtonYOffset();

        /**
         * @brief Get the CenterPieceOffset for the Button menu type
         * @return float
         */
        float GetCenterPieceOffset();

        /**
         * @brief Get the number of rows for the Button Menu type
         * @return int
         */
        int GetNumRows();

        /**
         * @brief Get the RowStartingX for the Button menu type
         * @param num_row Row muber
         * @return int
         */
        int GetRowStartingX( int num_row );

        /**
         * @brief Get the RowButtonXOffset for the Button menu type
         * @param num_row Row number
         * @return int
         */
        int GetRowButtonXOffset( int num_row );

        /**
         * @brief Get the number of elements in a row for the Button menu type
         * @param num_row Row number
         * @return int
         */
        int GetRowNumElements( int num_row );

        /**
         * @brief Get the fields of the element for the Button menu type
         * @param num_row Row number
         * @param num_element Element number
         * @return RowElementFields
         */
        RowElementFields GetRowElementFields( int num_row, int num_element );
    }

    namespace animations {
        inline nlohmann::json animation_file;
        inline std::string animation_file_path;

        /**
         * @struct AnimationElementsFields
         * @brief Fields of the elements in the .json configuration file
         */
        struct AnimationElementsFields {
            std::string path;
            std::string name;
            int frame_number;
            int frame_to_load;
        };

        /**
         * @brief Set the .json file to parse
         * @param config_file_path Path to the .json configuration file
         */
        void SetConfigFile( const std::string& config_file_path );

        /**
         * @brief Get how manu animations there are
         * @return
         */
        int GetAnimationNumbers();

        /**
         * @brief Return the fields of that animation
         * @param num_animation Animation number
         * @return AnimationElementsFields
         */
        AnimationElementsFields GetAnimationElementsFields( int num_animation);
    }
}


#endif //HERION_HERO_JSONPARSERER_HPP