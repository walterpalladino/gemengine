#include <SDL2_mixer/SDL_mixer.h>

#include "core/sound/SoundManager.h"
#include "utils/Log.h"
#include "core/exceptions/ResourceLoadException.h"
#include "core/exceptions/CoreInitializationException.h"

SoundManager *SoundManager::instance = 0;

void SoundManager::Init()
{
    Log::GetInstance()->Info("SoundManager::Init", "SoundManager Initializing");
    // TTF_Init();
    //  TODO : Change to parameter to select when use or not antialiasing
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        Log::GetInstance()->Info("SoundManager::Init", "SDL2_mixer could not be initialized. SDL_Error: %s", SDL_GetError());
        throw CoreInitializationException(SDL_GetError());
    }
}

void SoundManager::Clean()
{
    Log::GetInstance()->Info("SoundManager::Clean", "SoundManager Shutting Down");

    for (auto &[soundName, soundPointer] : sounds)
    {
        Log::GetInstance()->Info("SoundManager::Cleanup", "Deleting sound: %s", soundName.c_str());
        Mix_FreeChunk(soundPointer);
    }
    sounds.clear();

    for (auto &[trackName, trackPointer] : tracks)
    {
        Log::GetInstance()->Info("SoundManager::Cleanup", "Deleting track: %s", trackName.c_str());
        Mix_FreeMusic(trackPointer);
    }
    sounds.clear();

    Mix_CloseAudio();
}

string SoundManager::GetTrackKey(string sampleFileName, int size)
{
    return sampleFileName + "::" + std::to_string(size);
}

string SoundManager::GetSoundKey(string sampleFileName, int size)
{
    return sampleFileName + "::" + std::to_string(size);
}

Mix_Chunk *SoundManager::AddSound(string sampleFileName, int size)
{
    string key = GetSoundKey(sampleFileName, size);
    if (sounds.count(key) != 0)
    {
        return sounds[key];
    }
    Mix_Chunk *sound = Mix_LoadWAV(sampleFileName.c_str());
    if (sound == NULL)
    {
        string error_message = "Unable to load sound: " + sampleFileName + ". SDL2_mixer Error: " + SDL_GetError();
        Log::GetInstance()->Error("SoundManager::AddSound", error_message.c_str());
        throw ResourceLoadException(error_message.c_str());
    }
    sounds[key] = sound;
    return sound;
}

Mix_Music *SoundManager::AddTrack(string sampleFileName, int size)
{
    string key = GetTrackKey(sampleFileName, size);
    if (tracks.count(key) != 0)
    {
        return tracks[key];
    }
    Mix_Music *track = Mix_LoadMUS(sampleFileName.c_str());
    if (track == NULL)
    {
        string error_message = "Unable to load track: " + sampleFileName + ". SDL2_mixer Error: " + SDL_GetError();
        Log::GetInstance()->Error("SoundManager::AddTrack", error_message.c_str());
        throw ResourceLoadException(error_message.c_str());
    }
    tracks[key] = track;
    return track;
}
