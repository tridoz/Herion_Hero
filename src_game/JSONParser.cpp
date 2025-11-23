//
// Created by david on 23/11/2025.
//

#include "JSONParser.hpp"

//AUDIO
void JSONParser::audio::IncreaseMasterVolume() {
    std::ifstream audio_file_input(json_audio_file_path, std::ios::in );
    if ( !audio_file_input.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::audio",
            "IncreaseMasterVolume",
            "Error while opening file [" + json_audio_file_path + "] for input : " + strerror(errno)
            );
        return;
    }

    nlohmann::json json_audio;
    audio_file_input >> json_audio;

    double master_volume;

    if ( json_audio.contains("master_volume") ) {
        master_volume = json_audio["masterVolume"].get<double>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "IncreaseMasterVolume",
            "Error while parsing file [" + json_audio_file_path + "] : master_volume field doesn't exist"
            );
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
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "IncreaseMasterVolume",
            "Error while parsing file [" + json_audio_file_path + "] for output : " + strerror( errno )
            );
        return;
    }

    audio_file_output << json_audio.dump(4);
    audio_file_output.close();

}

void JSONParser::audio::DecreaseMasterVolume() {
    std::ifstream audio_file_input(json_audio_file_path, std::ios::in );
    if ( !audio_file_input.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::audio",
            "DecreaseMasterVolume",
            "Error while opening file [" + json_audio_file_path + "] for input : " + strerror(errno)
            );
        return;
    }

    nlohmann::json json_audio;
    audio_file_input >> json_audio;

    double master_volume;

    if ( json_audio.contains("master_volume") ) {
        master_volume = json_audio["masterVolume"].get<double>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "DecreaseMasterVolume",
            "Error while parsing file [" + json_audio_file_path + "] : master_volume field doesn't exist"
            );
        return;
    }

    master_volume -- ;

    if ( master_volume < 0 ) {
        master_volume = 0;
    }

    json_audio["master_volume"] = master_volume;

    audio_file_input.close();

    std::ofstream audio_file_output( json_audio_file_path , std::ios::out );
    if ( !audio_file_output.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "DecreaseMasterVolume",
            "Error while parsing file [" + json_audio_file_path + "] for output : " + strerror( errno )
            );
        return;
    }

    audio_file_output << json_audio.dump(4);
    audio_file_output.close();

}

void JSONParser::audio::IncreaseMusicVolume() {
    std::ifstream audio_file_input(json_audio_file_path, std::ios::in );
    if ( !audio_file_input.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::audio",
            "IncreaseMusicVolume",
            "Error while opening file [" + json_audio_file_path + "] for input : " + strerror(errno)
            );
        return;
    }

    nlohmann::json json_audio;
    audio_file_input >> json_audio;

    double music_volume;

    if ( json_audio.contains("music_volume") ) {
        music_volume = json_audio["music_volume"].get<double>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "IncreaseMusicVolume",
            "Error while parsing file [" + json_audio_file_path + "] : music_volume field doesn't exist"
            );
        return;
    }

    music_volume ++ ;

    if ( music_volume > 100 ) {
        music_volume = 100;
    }

    json_audio["music_volume"] = music_volume;

    audio_file_input.close();

    std::ofstream audio_file_output( json_audio_file_path , std::ios::out );
    if ( !audio_file_output.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "IncreaseMusicVolume",
            "Error while parsing file [" + json_audio_file_path + "] for output : " + strerror( errno )
            );
        return;
    }

    audio_file_output << json_audio.dump(4);
    audio_file_output.close();

}

void JSONParser::audio::DecreaseMusicVolume() {
    std::ifstream audio_file_input(json_audio_file_path, std::ios::in );
    if ( !audio_file_input.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::audio",
            "DecreaseMasterVolume",
            "Error while opening file [" + json_audio_file_path + "] for input : " + strerror(errno)
            );
        return;
    }

    nlohmann::json json_audio;
    audio_file_input >> json_audio;

    double music_volume;

    if ( json_audio.contains("music_volume") ) {
        music_volume = json_audio["music_volume"].get<double>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "DecreaseMasterVolume",
            "Error while parsing file [" + json_audio_file_path + "] : music_volume field doesn't exist"
            );
        return;
    }

    music_volume -- ;

    if ( music_volume < 0 ) {
        music_volume = 0;
    }

    json_audio["music_volume"] = music_volume;

    audio_file_input.close();

    std::ofstream audio_file_output( json_audio_file_path , std::ios::out );
    if ( !audio_file_output.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "DecreaseMusicVolume",
            "Error while parsing file [" + json_audio_file_path + "] for output : " + strerror( errno )
            );
        return;
    }

    audio_file_output << json_audio.dump(4);
    audio_file_output.close();

}

void JSONParser::audio::IncreaseSFXVolume() {
    std::ifstream audio_file_input(json_audio_file_path, std::ios::in );
    if ( !audio_file_input.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::audio",
            "IncreaseSFXVolume",
            "Error while opening file [" + json_audio_file_path + "] for input : " + strerror(errno)
            );
        return;
    }

    nlohmann::json json_audio;
    audio_file_input >> json_audio;

    double sfx_volume;

    if ( json_audio.contains("sfx_volume") ) {
        sfx_volume = json_audio["sfx_volume"].get<double>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "IncreaseSFXVolume",
            "Error while parsing file [" + json_audio_file_path + "] : sfx_volume field doesn't exist"
            );
        return;
    }

    sfx_volume ++ ;

    if ( sfx_volume > 100 ) {
        sfx_volume = 100;
    }

    json_audio["sfx_volume"] = sfx_volume;

    audio_file_input.close();

    std::ofstream audio_file_output( json_audio_file_path , std::ios::out );
    if ( !audio_file_output.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "IncreaseSFXVolume",
            "Error while parsing file [" + json_audio_file_path + "] for output : " +strerror( errno )
            );
        return;
    }

    audio_file_output << json_audio.dump(4);
    audio_file_output.close();

}

void JSONParser::audio::DecreaseSFXVolume() {
    std::ifstream audio_file_input(json_audio_file_path, std::ios::in );
    if ( !audio_file_input.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::audio",
            "DecreaseSFXVolume",
            "Error while opening file [" + json_audio_file_path + "] for input : " + strerror(errno)
            );
        return;
    }

    nlohmann::json json_audio;
    audio_file_input >> json_audio;

    double sfx_volume;

    if ( json_audio.contains("sfx_volume") ) {
        sfx_volume = json_audio["sfx_volume"].get<double>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "DecreaseSFXVolume",
            "Error while parsing file [" + json_audio_file_path + "] : sfx_volume field doesn't exist"
            );
        return;
    }

    sfx_volume -- ;

    if ( sfx_volume < 0 ) {
        sfx_volume = 0;
    }

    json_audio["sfx_volume"] = sfx_volume;

    audio_file_input.close();

    std::ofstream audio_file_output( json_audio_file_path , std::ios::out );
    if ( !audio_file_output.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "DecreaseSFXVolume",
            "Error while parsing file [" + json_audio_file_path + "] for output : " + strerror( errno )
            );
        return;
    }

    audio_file_output << json_audio.dump(4);
    audio_file_output.close();

}

void JSONParser::audio::ToggleMute() {
    std::ifstream audio_file_input(json_audio_file_path, std::ios::in );
    if ( !audio_file_input.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::audio",
            "ToggleMute",
            "Error while opening file [" + json_audio_file_path + "] for input : " + strerror(errno)
            );
        return;
    }

    nlohmann::json json_audio;
    audio_file_input >> json_audio;

    double mute;

    if ( json_audio.contains("mute") ) {
        mute = json_audio["mute"].get<bool>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "ToggleMute",
            "Error while parsing file [" + json_audio_file_path + "] : mute field doesn't exist"
            );
        return;
    }

    mute = !mute;

    json_audio["mute"] = mute;

    audio_file_input.close();

    std::ofstream audio_file_output( json_audio_file_path , std::ios::out );

    if ( !audio_file_output.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::audio",
            "ToggleMute",
            "Error while parsing file [" + json_audio_file_path + "] for output : " + strerror( errno )
            );
        return;
    }

    audio_file_output << json_audio.dump(4);
    audio_file_output.close();

}

void JSONParser::graphics::IncreaseResolution() {

    std::ifstream graphics_file( json_graphics_file_path, std::ios::in );
    if ( !graphics_file.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "IncreaseResolution",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror( errno )
            );
        return;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;

    int width = 0, height = 0;
    if (json_graphics.contains("resolution") &&
        json_graphics["resolution"].contains("width") &&
        json_graphics["resolution"].contains("height"))
    {
        width = json_graphics["resolution"]["width"].get<int>();
        height = json_graphics["resolution"]["height"].get<int>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "IncreaseResolution",
            "Error while parsing file [" + json_graphics_file_path + "] for output : resolutions {width: height} doesn't exist"
            );
        return;
    }

    const auto it = std::find(resolutions.begin(), resolutions.end(),
                        std::make_pair(width, height));
    int index = (it != resolutions.end()) ? (it - resolutions.begin()) : -1;

    if (index < 0 || index == resolutions.size() - 1) {
        return;
    }

    int new_width = resolutions[index + 1].first;
    int new_height = resolutions[index + 1].second;

    json_graphics["resolution"]["width"] = new_width;
    json_graphics["resolution"]["height"] = new_height;

    std::ofstream graphics_file_output( json_graphics_file_path , std::ios::out );
    if ( !graphics_file_output.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "IncreaseResolution",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror( errno )
        );
        return;
    }

    graphics_file_output << json_graphics.dump(4);
    graphics_file_output.close();
    changed = true;
}

void JSONParser::graphics::DecreaseResolution() {

    std::ifstream graphics_file(json_graphics_file_path, std::ios::in);
    if (!graphics_file.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "DecreaseResolution",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror(errno)
        );
        return;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    int width = 0, height = 0;
    if (json_graphics.contains("resolution") &&
        json_graphics["resolution"].contains("width") &&
        json_graphics["resolution"].contains("height"))
    {
        width = json_graphics["resolution"]["width"].get<int>();
        height = json_graphics["resolution"]["height"].get<int>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "DecreaseResolution",
            "Error while parsing file [" + json_graphics_file_path + "] for output : resolutions {width: height} doesn't exist"
        );
        return;
    }

    const auto it = std::find(resolutions.begin(), resolutions.end(),
                              std::make_pair(width, height));
    int index = (it != resolutions.end()) ? (it - resolutions.begin()) : -1;

    if (index <= 0) {
        return;
    }

    int new_width = resolutions[index - 1].first;
    int new_height = resolutions[index - 1].second;

    json_graphics["resolution"]["width"] = new_width;
    json_graphics["resolution"]["height"] = new_height;

    std::ofstream graphics_file_output(json_graphics_file_path, std::ios::out);
    if (!graphics_file_output.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "DecreaseResolution",
            "Error while opening file [" + json_graphics_file_path + "] for output : " + strerror(errno)
        );
        return;
    }

    graphics_file_output << json_graphics.dump(4);
    graphics_file_output.close();
    changed = true;

}

int JSONParser::graphics::GetWidth() {

    std::ifstream graphics_file(json_graphics_file_path, std::ios::in);
    if (!graphics_file.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "GetWidth",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror(errno)
        );
        return 0;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    if (json_graphics.contains("resolution") &&
        json_graphics["resolution"].contains("width"))
    {
        return json_graphics["resolution"]["width"].get<int>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "GetWidth",
            "Resolution width not found in file [" + json_graphics_file_path + "]"
        );
        return 0;
    }
}

int JSONParser::graphics::GetHeight() {
    std::ifstream graphics_file(json_graphics_file_path, std::ios::in);
    if (!graphics_file.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "GetHeight",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror(errno)
        );
        return 0;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    if (json_graphics.contains("resolution") &&
        json_graphics["resolution"].contains("height"))
    {
        return json_graphics["resolution"]["height"].get<int>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "GetHeight",
            "Resolution height not found in file [" + json_graphics_file_path + "]"
        );
        return 0;
    }
}

float JSONParser::graphics::GetScale() {
    std::ifstream graphics_file( json_graphics_file_path, std::ios::in );
    if ( !graphics_file.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "GetScale",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror( errno )
            );
        return 0;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;

    int width = 0, height = 0;
    if (json_graphics.contains("resolution") &&
        json_graphics["resolution"].contains("width") &&
        json_graphics["resolution"].contains("height"))
    {
        width = json_graphics["resolution"]["width"].get<int>();
        height = json_graphics["resolution"]["height"].get<int>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "GetScale",
            "Error while parsing file [" + json_graphics_file_path + "] for output : resolutions {width: height} doesn't exist"
            );
        return 0;
    }

    const auto it = std::find(resolutions.begin(), resolutions.end(),
                        std::make_pair(width, height));
    int index = (it != resolutions.end()) ? (it - resolutions.begin()) : -1;

    if (index < 0 || index > resolutions.size() - 1) {
        return 0;
    }

    return texture_scales[index];

}


bool JSONParser::graphics::Changed() {
    return changed;
}

void JSONParser::graphics::ChangesApplied() {
    changed = false;
}

