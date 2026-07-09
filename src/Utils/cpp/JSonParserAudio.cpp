//
// Created by david on 20/12/2025.
//

#include "../hpp/JSONParser.hpp"

//AUDIO
//

void JSONParser::audio::SetMasterVolume( int volume ) {
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


    if(volume > 100 ) {
        volume = 100;
    }

    if( volume < 0) {
        volume = 0;
    }


    json_audio["master_volume"] = volume;

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
    changed = true;
}
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
        master_volume = json_audio["master_volume"].get<double>();
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
    changed = true;

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
        master_volume = json_audio["master_volume"].get<double>();
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

    master_volume-- ;

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
    changed = true;

}

void JSONParser::audio::SetMusicVolume( int volume ) {
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


    if ( volume > 100 ) {
        volume = 100;
    }

    if ( volume < 0 ) {
        volume = 0;
    }

    json_audio["music_volume"] = volume;

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

    changed = true;

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

    changed = true;

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

    changed = true;

}

void JSONParser::audio::SetSFXVolume( int volume ) {
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

    if ( volume > 100 ) {
        volume = 100;
    }
    if( volume < 0 ) {
        volume = 0;
    }

    json_audio["sfx_volume"] = volume;

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

    changed = true;

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

    changed = true;

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

    changed = true;

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

float JSONParser::audio::GetMasterVolume() {
    std::ifstream audio_file;

    try {
      FileOpener::OpenFileInput( audio_file, json_audio_file_path );
    } catch ( HerionException::File::FileException& ex) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        throw;
    }

    nlohmann::json json_audio;
    audio_file >> json_audio;
    audio_file.close();

    if ( !json_audio.contains("master_volume") ) {
        THROW_FILE_MALFORMED( json_audio_file_path + "\t=> master_volume");
    }

    return json_audio["master_volume"].get<float>();
}
float JSONParser::audio::GetMusicVolume() {
    std::ifstream audio_file;

    try {
      FileOpener::OpenFileInput( audio_file, json_audio_file_path );
    } catch ( HerionException::File::FileException& ex) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        throw;
    }

    nlohmann::json json_audio;
    audio_file >> json_audio;
    audio_file.close();

    if ( !json_audio.contains("music_volume") ) {
        THROW_FILE_MALFORMED( json_audio_file_path + "\t=> music_volume");
    }

    return json_audio["music_volume"].get<float>();
}
float JSONParser::audio::GetSFXVolume() {
    std::ifstream audio_file;

    try {
      FileOpener::OpenFileInput( audio_file, json_audio_file_path );
    } catch ( HerionException::File::FileException& ex) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        throw;
    }

    nlohmann::json json_audio;
    audio_file >> json_audio;
    audio_file.close();

    if ( !json_audio.contains("sfx_volume") ) {
        THROW_FILE_MALFORMED( json_audio_file_path + "\t=> sfx_volume");
    }

    return json_audio["sfx_volume"].get<float>();
}

bool JSONParser::audio::Changed() {
    return changed;
}

void JSONParser::audio::ChangesApplied() {
    changed = false;
}
