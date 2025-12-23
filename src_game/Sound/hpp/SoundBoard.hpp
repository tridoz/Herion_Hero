//
// Created by david on 21/12/2025.
//

#ifndef HERION_HERO_SOUNDBOARD_HPP
#define HERION_HERO_SOUNDBOARD_HPP

#define MINIAUDIO_IMPLEMENTATION

#include "../../headers_only_dependencies/miniaudio.h"
#include "../../Utils/hpp/Logger.hpp"

#include <string>
#include <unordered_map>

class SoundBoard {

private:
    ma_engine engine{};
    std::unordered_map<std::string, ma_sound> sounds;

public:
    SoundBoard();
    ~SoundBoard();

    void LoadSound(const std::string& id, const std::string& filepath);

    void PlaySound(const std::string& id);

    void StopSound(const std::string &id);

    void StopAll();


};

#endif // SOUNDBOARD_HPP

