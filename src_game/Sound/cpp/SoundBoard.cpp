#include "../hpp/SoundBoard.hpp"
#include <iostream>

SoundBoard::SoundBoard() {
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        std::cerr << "Errore inizializzazione motore audio\n";
    }
}

SoundBoard::~SoundBoard() {

    for (auto& pair : sounds) {
        ma_sound_uninit(&pair.second);
    }
    ma_engine_uninit(&engine);
}

bool SoundBoard::loadSound(const std::string& id, const std::string& filepath) {
    ma_sound sound;
    if (ma_sound_init_from_file(&engine, filepath.c_str(), 0, NULL, NULL, &sound) != MA_SUCCESS) {
        std::cerr << "Errore caricamento suono: " << filepath << "\n";
        return false;
    }
    sounds[id] = sound;
    return true;
}

bool SoundBoard::playSound(const std::string& id) {
    auto it = sounds.find(id);
    if (it == sounds.end()) {
        std::cerr << "Suono non trovato: " << id << "\n";
        return false;
    }
    if (ma_sound_start(&it->second) != MA_SUCCESS) {
        std::cerr << "Errore riproduzione suono: " << id << "\n";
        return false;
    }
    return true;
}

void SoundBoard::stopAll() {
    for (auto& pair : sounds) {
        ma_sound_stop(&pair.second);
    }
}
