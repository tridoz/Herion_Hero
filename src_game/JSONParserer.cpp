//
// Created by david on 23/11/2025.
//

#include "JSONParserer.hpp"
const std::string JSONParserer::json_audio_file_path =  "../settings/audio.json";
const std::string JSONParserer::json_controls_file_path =   "../settings/controls.json";
const std::string JSONParserer::json_gameplay_file_path =   "../settings/gameplay.json";
const std::string JSONParserer::json_graphics_file_path =   "../settings/graphics.json";
const std::string JSONParserer::json_ui_file_path =         "../settings/ui.json";

void JSONParserer::IncreaseMasterVolume() {
    std::ifstream audio_file_input( json_audio_file_path, std::ios::in );
    if ( !audio_file_input.is_open() ) {
        //need logging
        return;
    }

    //need logging
    nlohmann::json json_audio;
    audio_file_input >> json_audio;

    double master_volume;

    if ( json_audio.contains("master_volume") ) {
        master_volume = json_audio["masterVolume"].get<double>();
    } else {
        //need logging
        return;
    }

    master_volume ++ ;

    if ( master_volume > 100 ) {
        master_volume = 100;
    }

    json_audio["master_volume"] = master_volume;

    audio_file_input.close();

    std::ofstream audio_file_output( json_audio_file_path , std::ios::out );
    if ( !audio_file_output.is_open() ) {
        //need logging
        return;
    }

    audio_file_output << json_audio.dump(4);
    audio_file_output.close();
}
