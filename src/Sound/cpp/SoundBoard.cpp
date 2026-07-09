#include "../hpp/SoundBoard.hpp"

#include "../../Utils/hpp/JSONParser.hpp"

MIX_Mixer* SoundBoard::mixer = nullptr;
MIX_Track* SoundBoard::track = nullptr;
std::unordered_map < std::string, MIX_Audio* > SoundBoard::sounds;

void SoundBoard::Init() {
    mixer = nullptr;
    track = nullptr;


    if ( !MIX_Init() == 0 ) {
        Logger::LogErr(
          std::time(nullptr),
          "INITIALIZE",
          "SoundBoard",
          "Init",
          "Failed to MIX_Init " + std::string( SDL_GetError() )
        );
    }

    mixer = MIX_CreateMixerDevice( SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if ( !mixer ) {
        Logger::LogErr(
          std::time(nullptr),
          "INITIALIZE",
          "SoundBoard",
          "Init",
          "Failed to initialize mixer " + std::string( SDL_GetError() )
        );
    }
}

void SoundBoard::LoadSound(const std::string &id, const std::string &filepath) {
    MIX_Audio* audio = MIX_LoadAudio( mixer, filepath.c_str() , false );

    if ( !audio ) {
        Logger::LogErr(
          std::time(nullptr),
          "INITIALIZE",
          "SoundBoard",
          "LoadSound",
          "Failed to initialize audio ( " + id + " ; " + filepath + " ) : " + std::string( SDL_GetError() )
        );
    }

    sounds.emplace(id, audio);
}

void SoundBoard::PlaySound(const std::string &id) {
    track = MIX_CreateTrack(mixer);
    if ( !track ) {
        Logger::LogErr(
          std::time(nullptr),
          "INITIALIZE",
          "SoundBoard",
          "LoadSound",
          "Failed to initialize audio ( " + id + " ) : " + std::string( SDL_GetError() )
        );
    }

    MIX_SetTrackAudio( track, sounds.at(id) );
    MIX_SetTrackGain( track, JSONParser::audio::GetMasterVolume() / 100 );
    MIX_PlayTrack( track, 0);

}
