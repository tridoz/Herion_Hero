//
// Created by david on 23/11/2025.
//

#ifndef HERION_HERO_JSONPARSERER_HPP
#define HERION_HERO_JSONPARSERER_HPP

#include "../../../headers_only_dependencies/json.hpp"
#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "FileOpener.hpp"

#include <fstream>
#include <string>

#include "Logger.hpp"
#include "STRINGS.hpp"

namespace JSONParser {

    namespace audio {
        inline const std::string json_audio_file_path = Strings::Settings::Paths::json_audio_settings_file_path;
        inline bool changed = false;

        auto SetMasterVolume(int) -> void;
        auto IncreaseMasterVolume() -> void;
        auto DecreaseMasterVolume() -> void;

        auto SetMusicVolume(int) -> void;
        auto IncreaseMusicVolume() -> void;
        auto DecreaseMusicVolume() -> void;

        auto SetSFXVolume(int) -> void;
        auto IncreaseSFXVolume() -> void;
        auto DecreaseSFXVolume() -> void;

        auto ToggleMute() -> void;

        auto GetMasterVolume() -> float;
        auto GetMusicVolume() -> float;
        auto GetSFXVolume() -> float;

        auto Changed() -> bool;
        auto ChangesApplied() -> void;
    } // namespace audio

    namespace controls {}

    namespace gameplay {}

    namespace graphics {

        static inline const std::vector<int> allowedFPS = {10, 15, 20, 30, 45, 60, 120, 180, 240, 360, 500};
        inline const std::string json_graphics_file_path = Strings::Settings::Paths::json_graphics_settings_file_path;
        inline bool changed = false;

        inline const std::vector<std::pair<int, int>> resolutions{
            {640, 360}, {854, 480}, {960, 540}, {1280, 720}, {1600, 900}, {1920, 1080}, {2560, 1440}, {3840, 2160}
        };
        inline const std::vector<float> texture_scales{0.25, 0.333, 0.375, 0.5, 0.625, 0.75, 1.0, 1.5};
        auto IncreaseResolution() -> void;
        auto DecreaseResolution() -> void;
        auto GetWidth() -> int;
        auto GetHeight() -> int;
        auto IncreaseFPSLimit() -> void;
        auto DecreaseFPSLimit() -> void;
        auto Changed() -> bool;
        auto ChangesApplied() -> void;
        auto GetScale() -> float;

        auto GetFrameRate() -> int;

    } // namespace graphics

    namespace ui {}

    namespace menu_configuration {
        inline nlohmann::json config_file;
        inline std::string config_file_path;

        struct RowElementFields {
            std::string type;
            std::string id;

            std::optional<std::string> text;
            std::optional<std::string> action;
            std::optional<std::string> value_to_set;
            std::optional<std::string> return_value;
            std::optional<float> max_value;
            std::optional<float> min_value;
            std::optional<float> step;
            std::optional<float> length;
            std::optional<float> slider_bar_offset;
        };
        auto SetConfigFile(const std::string&) -> void;
        auto GetBackgroundImagePath() -> std::string;
        auto GetMenuType() -> std::string;
        auto GetButtonStyle() -> std::string;
        auto GetFontStyle() -> std::string;
        auto GetCharWidth() -> float;
        auto GetCmd() -> std::string;
        auto GetDirectoryTextureSize() -> int;
        auto GetFileTextureSize() -> int;
        auto GetStartY() -> float;
        auto GetButtonYOffset() -> float;
        auto GetCenterPieceOffset() -> float;
        auto GetNumRows() -> int;
        auto GetRowStartingX(int) -> int;
        auto GetRowButtonXOffset(int) -> int;
        auto GetRowNumElements(int) -> int;
        auto GetRowElementFields(int, int) -> RowElementFields;
    } // namespace menu_configuration

    namespace animations {
        inline nlohmann::json animation_file;
        inline std::string animation_file_path;
        struct AnimationElementsFields {
            std::string path;
            std::string name;
            int frame_number;
            int frame_to_load;
        };

        auto SetConfigFile(const std::string&) -> void;
        auto GetAnimationNumbers() -> int;
        auto GetAnimationElementsFields(int) -> AnimationElementsFields;
    } // namespace animations

    namespace entities {

        struct EntityStats {
            int hp;
            int mana;
            int stamina;

            [[nodiscard]] auto ToString() const -> std::string {
                return "{\n"
                       "  hp: " +
                       std::to_string(hp) + "\n" + "  mana: " + std::to_string(mana) + "\n" +
                       "  stamina: " + std::to_string(stamina) +
                       "\n"
                       "}";
            }
        };

        struct EntityCoordinates {
            float x;
            float y;

            [[nodiscard]] auto ToString() const -> std::string {
                return "{\n"
                       "  x: " +
                       std::to_string(x) + "\n" + "  y: " + std::to_string(y) +
                       "\n"
                       "}";
            }
        };

        struct EntityPosition {
            std::string plane;
            EntityCoordinates coordinates;

            [[nodiscard]] auto ToString() const -> std::string {
                return "{\n"
                       "  plane: " +
                       plane +
                       "\n"
                       "  coordinates: " +
                       coordinates.ToString() +
                       "\n"
                       "}";
            }
        };

        struct EntityProperties {
            std::string type;
            std::string animations_file_path;
            std::optional<EntityStats> stats;
            std::optional<EntityPosition> position;

            [[nodiscard]] auto ToString() const -> std::string {
                std::string result = "EntityProperties {\n"
                                     "  type: " +
                                     type +
                                     "\n"
                                     "  animations_file_path: " +
                                     animations_file_path + "\n";

                if (stats.has_value()) {
                    result += "  stats: " + stats->ToString() + "\n";
                } else {
                    result += "  stats: null\n";
                }

                if (position.has_value()) {
                    result += "  position: " + position->ToString() + "\n";
                } else {
                    result += "  position: null\n";
                }

                result += "}";

                return result;
            }
        };

        [[nodiscard]] auto GetEntityProperties(const std::string&) -> std::vector<struct EntityProperties>;
        [[nodiscard]] auto GetEntitiTextureFilePath(const std::string&, const std::string&) -> std::string;
        [[nodiscard]] auto GetEntityLimit(const std::string&, const std::string&) -> int;
    } // namespace entities

} // namespace JSONParser

#endif // HERION_HERO_JSONPARSERER_HPP
