//
// Created by tridoz on 25/05/26.
//

#ifndef HERION_HERO_STRINGS_HPP
#define HERION_HERO_STRINGS_HPP
#include <string>

namespace Strings {

    namespace Sounds::Paths{
        const std::string all_sounds_path = "sounds/";
    };

    namespace Textures::Paths{
        const std::string all_textures_path = "Assets/all_textures.txt";
    }

    namespace Menus {
        namespace Main_Window {
            namespace Paths {
                const std::string main_window_general_path = "configs/menus/main_window/";

                const std::string main_menu_config_path = main_window_general_path + "main_menu.json";
                const std::string general_settings_menu_config_path = main_window_general_path + "general_settings_menu.json";
                const std::string graphics_settings_menu_config_path = main_window_general_path + "graphics_settings_menu.json";
                const std::string audio_settings_menu_config_path = main_window_general_path + "audio_settings_menu.json";
                const std::string pause_menu_config_path = main_window_general_path + "pause_menu.json";
                const std::string editor_menu_config_path = main_window_general_path + "editor_menu.json";

            }

            namespace Names {
                const std::string main_menu_name = "MAIN_MENU";
                const std::string general_settings_menu_name = "GENERAL_SETTINGS_MENU";
                const std::string graphics_settings_menu_name = "GRAPHICS_SETTINGS_MENU";
                const std::string audio_settings_menu_name = "AUDIO_SETTINGS_MENU";
                const std::string pause_menu_name = "PAUSE_MENU";
                const std::string editor_menu_name = "EDITOR_MENU";

            }

        }

        namespace Level_Editors_Window {
            namespace Paths {
                const std::string editor_window_general_path = "configs/menus/level_editors_windows/";

                const std::string texture_selection_menu_config_path = editor_window_general_path + "directory_texture_selection.json";
                const std::string action_selection_menu_config_path = editor_window_general_path + "action_selection.json";
            }

            namespace Names {
                const std::string texture_selection_menu_name = "TEXTURE_SELECTIONS";
                const std::string action_selection_menu_name = "ACTION_SELECTION";
            }
        }


    }

    namespace TextureManagers::Names {
        constexpr std::string main_texture_manager_name = "MAIN";
        constexpr std::string texture_selection_menu_name = "EDITOR";
        constexpr std::string action_selection_menu_name = "ACTION";
    }

    namespace Animations::Player::Paths {
        const std::string animation_config_file_path = "configs/animations/player.json";
    }

    namespace Settings::Paths {
        const std::string json_audio_settings_file_path = "settings/audio.json";
        const std::string json_graphics_settings_file_path = "settings/graphics.json";
    }

};



#endif //HERION_HERO_STRINGS_HPP
