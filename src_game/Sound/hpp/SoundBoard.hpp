//
// Created by david on 21/12/2025.
//

#ifndef HERION_HERO_SOUNDBOARD_HPP
#define HERION_HERO_SOUNDBOARD_HPP

#define MINIAUDIO_IMPLEMENTATION

#include <SDL3/SDL.h>
#include <SDL3/SDL_mixer.h>

#include "../../Utils/hpp/Logger.hpp"

#include <string>
#include <unordered_map>

class SoundBoard {
    MIX_Mixer *mixer;
    MIX_Track *track;

    std::unordered_map< std::string, MIX_Audio* > sounds;

public:

    SoundBoard();

    void LoadSound(const std::string& id, const std::string& filepath );
    void PlaySound(const std::string& id);

};

#endif // SOUNDBOARD_HPP



