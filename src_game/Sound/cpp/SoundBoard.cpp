#include "../hpp/SoundBoard.hpp"

SoundBoard::SoundBoard() {
    if ( !MIX_Init() == 0 ) {

    }

    this->mixer = MIX_CreateMixerDevice( SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if ( !this->mixer ) {

    }
}

void SoundBoard::LoadSound(const std::string &id, const std::string &filepath) {
    MIX_Audio* audio = MIX_LoadAudio( this->mixer, filepath.c_str() , false );
    if ( !audio ) {

    }

    sounds.emplace(id, audio);
}

void SoundBoard::PlaySound(const std::string &id) {
    this->track = MIX_CreateTrack(this->mixer);
    if ( !this->track ) {

    }

    MIX_SetTrackAudio( this->track, sounds.at(id) );
    MIX_PlayTrack( track, 0);


}
