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

        void IncreaseResolution();
        void DecreaseResolution();

        int GetWidth();
        int GetHeight();

        void IncreaseFPSLimit();
        void DecreaseFPSLimit();

        bool Changed();
        void ChangesApplied();

        float GetScale();

        int GetFrameRate();

    }

    namespace ui {

    }

    namespace menu_configuration {
        inline nlohmann::json config_file;
        inline std::string config_file_path;
        struct RowElementFields {
            std::string type;
            std::string text;
            std::optional<std::string> action;
            std::string id;
        };

        void SetConfigFile( const std::string& config_file_path );

        std::string GetBackgroundImagePath();
        std::string GetMenuType();
        std::string GetCmd();

        int GetTabIndentSubdirectory();
        int GetDirectoryTextureSize();
        int GetFileTextureSize();

        float GetStartY();
        float GetButtonYOffset();
        float GetCenterPieceOffset();

        int GetNumRows();

        int GetRowStartingX( int num_row );
        int GetRowButtonXOffset( int num_row );

        int GetRowNumElements( int num_row );

        RowElementFields GetRowElementFields( int num_row, int num_element );
    }

    namespace animations {
        inline nlohmann::json animation_file;
        inline std::string animation_file_path;
        struct AnimationElementsFields {
            std::string path;
            std::string name;
            int frame_number;
            int frame_to_load;
        };
        void SetConfigFile( const std::string& config_file_path );
        int GetAnimationNumbers();
        AnimationElementsFields GetAnimationElementsFields( int num_animation);
    }
}


#endif //HERION_HERO_JSONPARSERER_HPP