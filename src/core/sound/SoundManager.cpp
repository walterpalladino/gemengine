#include <SDL2_mixer/SDL_mixer.h>

#include "core/sound/SoundManager.h"
#include "utils/Log.h"
#include "core/Config.h"

#include "core/exceptions/ResourceLoadException.h"
#include "core/exceptions/CoreInitializationException.h"

SoundManager *SoundManager::instance = 0;

void SoundManager::Init()
{
    Log::GetInstance()->Info("SoundManager::Init", "SoundManager Initializing");
    //  TODO : Change to parameter to config file settings
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
    tracks.clear();

    Mix_CloseAudio();
}

string SoundManager::GetTrackKey(string sampleFileName)
{
    return sampleFileName;
}

string SoundManager::GetSoundKey(string sampleFileName)
{
    return sampleFileName;
}

Mix_Chunk *SoundManager::AddSound(string name, string sampleFileName)
{
    string key = GetSoundKey(name);
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

Mix_Music *SoundManager::AddTrack(string name, string sampleFileName)
{
    string key = GetTrackKey(name);
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
    cout << "Track [" << sampleFileName << "][" << key << "] added" << endl;
    tracks[key] = track;
    return track;
}

void SoundManager::PlayTrack(string trackName, int loops)
{

    string key = GetTrackKey(trackName);

    if (tracks.count(key) == 0)
    {
        // cout << "Track [" << trackName << "][" << key << "] not found" << endl;
        Log::GetInstance()->Error("SoundManager::PlayTrack", "Track [%s] not found", trackName.c_str());
        return;
    }
    if (Mix_PlayingMusic() == 0) //  If no music is playing
    {
        int status = Mix_PlayMusic(tracks[key], loops);

        if (status == -1)
        {
            // cout << "Track [" << trackName << "][" << key << "] not found" << endl;
            // cout << "SDL2_mixer Error: " << SDL_GetError() << endl;
            // cout << tracks[key] << endl;
            Log::GetInstance()->Error("SoundManager::PlayTrack", "Unable to play track: %s. SDL2_mixer Error: %s", trackName.c_str(), SDL_GetError());
            trackPlaying = "";
        }
        else
        {
            trackPlaying = key;
        }
    }
    else
    {
        cout << "Already playing track" << endl;
    }
    //  TODO : Now just ignoring. Should I cancel and play a new one?
}

int SoundManager::PlaySound(string soundName, int loops)
{
    string key = GetSoundKey(soundName);
    if (sounds.count(key) == 0)
    {
        Log::GetInstance()->Error("SoundManager::PlaySound", "Sound [%s] not found", soundName.c_str());
        return -1;
    }
    //  TODO : If sound is already playing, should I cancel and play a new one?
    if (soundChannels.count(key) == 0)
    {
        soundChannels[key] = Mix_PlayChannel(-1, sounds[key], loops);
    }
    return soundChannels[key];
}

void SoundManager::StopSound(string soundName)
{
    string key = GetSoundKey(soundName);
    if (soundChannels.count(key) != 0)
    {
        Mix_HaltChannel(soundChannels[key]);
        soundChannels.erase(key);
    }
}

void SoundManager::StopTrack(string trackName)
{
    string key = GetTrackKey(trackName);
    if (Mix_PlayingMusic() != 0)
    {
        Mix_HaltMusic();
    }
    trackPlaying = "";
}

void SoundManager::JSONParseSound(json data)
{
    string name = data["name"];
    string src = data["src"];
    string sampleFileName = Config::Instance()->config_data.resource_folder + "/" + src;
    AddSound(name, sampleFileName);
}

void SoundManager::JSONParseTrack(json data)
{
    string name = data["name"];
    string src = data["src"];
    string sampleFileName = Config::Instance()->config_data.resource_folder + "/" + src;
    AddTrack(name, sampleFileName);
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