#include "../hpp/SoundBoard.hpp"
#include <iostream>


SoundBoard::SoundBoard() {
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        Logger::LogErr(
            std::time(nullptr),
            "PLAYING",
            "SoundBoard",
            "PlaySound",
            "Error while initializing the sound engine : " + std::string( strerror( errno ) )
            );
    }
}

SoundBoard::~SoundBoard() {

    for (auto& pair : sounds) {
        ma_sound_uninit(&pair.second);
    }
    ma_engine_uninit(&engine);
}

void SoundBoard::LoadSound(const std::string& id, const std::string& filepath) {
    ma_sound sound;
    if (ma_sound_init_from_file(&engine, filepath.c_str(), 0, NULL, NULL, &sound) != MA_SUCCESS) {
        Logger::LogErr(
        std::time(nullptr),
        "PLAYING",
        "SoundBoard",
        "PlaySound",
        "Error while playing file with id [" + id + "] : " + strerror( errno )
        );
        return;
    }
    sounds[id] = sound;
}

void SoundBoard::PlaySound(const std::string &id) {
    auto it = sounds.find(id);
    if (it == sounds.end()) {
        Logger::LogErr(
            std::time(nullptr),
            "PLAYING",
            "SoundBoard",
            "PlaySound",
            "Error while playing file with id [" + id + "] : " + strerror( errno )
            );
        return;
    }
    if (ma_sound_start(&it->second) != MA_SUCCESS) {
        Logger::LogErr(
            std::time(nullptr),
            "PLAYING",
            "SoundBoard",
            "PlaySound",
            "Error while playing sound with id [" + id + "] : " + strerror( errno )
            );
        return;
    }
    return;
}

void SoundBoard::StopSound( const std::string& id ) {
    auto it = sounds.find( id );

    if ( it == sounds.end() ) {
        Logger::LogErr(
            std::time(nullptr),
            "STOPPING",
            "SoundBoard",
            "StopSound",
            "Error while stopping sound with id [" + id + "] : " + strerror( errno )
            );
        return;
    }

    ma_sound_stop(&it->second);
    return;
}

void SoundBoard::StopAll() {
    for (auto& pair : sounds) {
        ma_sound_stop(&pair.second);
    }
}
