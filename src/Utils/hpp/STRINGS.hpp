//
// Created by tridoz on 25/05/26.
//

#ifndef HERION_HERO_STRINGS_HPP
#define HERION_HERO_STRINGS_HPP
#include <string>

namespace Strings {

    namespace Sounds::Paths {
        inline const std::string all_sounds_path = "sounds/";
    };

    namespace Textures::Paths {
        inline const std::string all_textures_path = "Assets/all_textures.txt";
    }

    namespace Menus {
        namespace Main_Window {
            namespace Paths {
                inline const std::string main_window_general_path = "configs/menus/main_window/";

                inline const std::string main_menu_config_path = main_window_general_path + "main_menu.json";
                inline const std::string general_settings_menu_config_path =
                    main_window_general_path + "general_settings_menu.json";
                inline const std::string graphics_settings_menu_config_path =
                    main_window_general_path + "graphics_settings_menu.json";
                inline const std::string audio_settings_menu_config_path =
                    main_window_general_path + "audio_settings_menu.json";
                inline const std::string pause_menu_config_path = main_window_general_path + "pause_menu.json";
                inline const std::string editor_menu_config_path = main_window_general_path + "editor_menu.json";

            } // namespace Paths

            namespace Names {
                inline const std::string main_menu_name = "MAIN_MENU";
                inline const std::string general_settings_menu_name = "GENERAL_SETTINGS_MENU";
                inline const std::string graphics_settings_menu_name = "GRAPHICS_SETTINGS_MENU";
                inline const std::string audio_settings_menu_name = "AUDIO_SETTINGS_MENU";
                inline const std::string pause_menu_name = "PAUSE_MENU";
                inline const std::string editor_menu_name = "EDITOR_MENU";

            } // namespace Names

        } // namespace Main_Window

        namespace Level_Editors_Window {
            namespace Paths {
                inline const std::string editor_window_general_path = "configs/menus/level_editors_windows/";

                inline const std::string texture_selection_menu_config_path =
                    editor_window_general_path + "directory_texture_selection.json";
                inline const std::string action_selection_menu_config_path =
                    editor_window_general_path + "action_selection.json";
                inline const std::string entity_selection_menu_config_path =
                    editor_window_general_path + "entity_selection_menu.json";
            } // namespace Paths

            namespace Names {
                inline const std::string texture_selection_menu_name = "TEXTURE_SELECTIONS";
                inline const std::string action_selection_menu_name = "ACTION_SELECTION";
                inline const std::string entity_selection_menu_name = "ENTITY_SELECTION";
            } // namespace Names
        } // namespace Level_Editors_Window

    } // namespace Menus

    namespace TextureManagers::Names {
        inline const std::string main_texture_manager_name = "MAIN";
        inline const std::string texture_selection_menu_name = "EDITOR";
        inline const std::string action_selection_menu_name = "ACTION";
        inline const std::string entity_seleciton_menu_name = "ENTITY";
    } // namespace TextureManagers::Names

    namespace Animations::Player::Paths {
        inline const std::string animation_config_file_path = "configs/animations/player.json";
    }

    namespace Settings::Paths {
        inline const std::string json_audio_settings_file_path = "settings/audio.json";
        inline const std::string json_graphics_settings_file_path = "settings/graphics.json";
    } // namespace Settings::Paths

}; // namespace Strings

#endif // HERION_HERO_STRINGS_HPP
