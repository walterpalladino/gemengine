#include <SDL2_mixer/SDL_mixer.h>

#include "core/sound/SoundManager.h"
#include "utils/Log.h"
#include "core/config/Config.h"

#include "core/exceptions/ResourceLoadException.h"
#include "core/exceptions/CoreInitializationException.h"

SoundManager *SoundManager::instance = 0;

void SoundManager::Init()
{
    Log::Instance()->Info("SoundManager::Init", "SoundManager Initializing");
    //  int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);
    //      frequency	the frequency to playback audio at (in Hz).
    //                  22050 good for games
    //                  44100 better for audio tracks.
    //      format	    audio format, one of SDL's AUDIO_* values.
    //      channels	number of channels (1 is mono, 2 is stereo, etc).
    //      chunksize	audio buffer size in sample FRAMES (total samples divided by channel count).
    //  Return Value
    //      Returns 0 if successful, -1 on error.
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        Log::Instance()->Info("SoundManager::Init", "SDL2_mixer could not be initialized. SDL_Error: %s", SDL_GetError());
        throw CoreInitializationException(SDL_GetError());
    }
}

void SoundManager::Cleanup()
{
    Log::Instance()->Info("SoundManager::Clean", "SoundManager Shutting Down");

    for (auto &[soundName, soundPointer] : sounds)
    {
        Log::Instance()->Info("SoundManager::Cleanup", "Deleting sound: %s", soundName.c_str());
        Mix_FreeChunk(soundPointer);
    }
    sounds.clear();

    for (auto &[trackName, trackPointer] : tracks)
    {
        Log::Instance()->Info("SoundManager::Cleanup", "Deleting track: %s", trackName.c_str());
        Mix_FreeMusic(trackPointer);
    }
    tracks.clear();

    Mix_CloseAudio();
    Mix_Quit();
}

Mix_Chunk *SoundManager::AddSound(string sampleFileName)
{
    if (sounds.count(sampleFileName) != 0)
    {
        return sounds[sampleFileName];
    }
    Mix_Chunk *sound = Mix_LoadWAV(sampleFileName.c_str());
    if (sound == NULL)
    {
        string error_message = "Unable to load sound: " + sampleFileName + ". SDL2_mixer Error: " + SDL_GetError();
        Log::Instance()->Error("SoundManager::AddSound", error_message.c_str());
        throw ResourceLoadException(error_message.c_str());
    }
    sounds[sampleFileName] = sound;
    return sound;
}

Mix_Music *SoundManager::AddTrack(string sampleFileName)
{
    if (tracks.count(sampleFileName) != 0)
    {
        return tracks[sampleFileName];
    }
    Mix_Music *track = Mix_LoadMUS(sampleFileName.c_str());
    if (track == NULL)
    {
        string error_message = "Unable to load track: " + sampleFileName + ". SDL2_mixer Error: " + SDL_GetError();
        Log::Instance()->Error("SoundManager::AddTrack", error_message.c_str());
        throw ResourceLoadException(error_message.c_str());
    }
    tracks[sampleFileName] = track;
    return track;
}

void SoundManager::PlayTrack(Mix_Music *track, int loops)
{
    if (Mix_PlayMusic(track, loops) == -1)
    {
        Log::Instance()->Error("SoundManager::PlayTrack", "Unable to play track. SDL2_mixer Error: %s", SDL_GetError());
    }
}

int SoundManager::PlaySound(Mix_Chunk *sound, int loops)
{
    return Mix_PlayChannel(-1, sound, loops);
}

void SoundManager::StopSound(int channel)
{
    Mix_HaltChannel(channel);
}

void SoundManager::StopTrack()
{
    if (Mix_PlayingMusic() != 0)
    {
        Mix_HaltMusic();
    }
}

int SoundManager::SetMasterVolume(int volume)
{
    return Mix_MasterVolume(volume); // 0 - 128
}

int SoundManager::SetTrackVolume(int volume)
{
    return Mix_VolumeMusic(volume);
}

int SoundManager::SetSoundChannelVolume(int channel, int volume)
{
    return Mix_Volume(channel, volume);
}