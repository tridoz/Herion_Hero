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
    static MIX_Mixer* mixer;
    static MIX_Track* track;

    static std::unordered_map<std::string, MIX_Audio*> sounds;

  public:
    static auto Init() -> void;
    static auto LoadSound(const std::string&, const std::string&) -> void;
    static auto PlaySound(const std::string&) -> void;
};

#endif // SOUNDBOARD_HPP
