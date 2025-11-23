//
// Created by david on 23/11/2025.
//

#ifndef HERION_HERO_JSONPARSERER_HPP
#define HERION_HERO_JSONPARSERER_HPP

#include "../headers_only_dependencies/json.hpp"

#include <fstream>

class JSONParserer {
private:
    const static std::string json_audio_file_path;
    const static std::string json_controls_file_path;
    const static std::string json_gameplay_file_path;
    const static std::string json_graphics_file_path;
    const static std::string json_ui_file_path;

public:
    static void IncreaseMasterVolume();
};


#endif //HERION_HERO_JSONPARSERER_HPP