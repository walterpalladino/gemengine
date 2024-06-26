#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL2_mixer/SDL_mixer.h>

#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class SoundManager
{
public:
    static SoundManager *Instance()
    {
        if (instance == 0)
        {
            instance = new SoundManager();
        }
        return instance;
    }

    void Init();
    void Cleanup();

    Mix_Music *AddTrack(string sampleFileName);
    Mix_Chunk *AddSound(string sampleFileName);

    void PlayTrack(Mix_Music *track, int loops = -1);
    int PlaySound(Mix_Chunk *sound, int loops = 0);

    void StopTrack();
    void StopSound(int channel);

    int SetMasterVolume(int volume);
    int SetTrackVolume(int volume);
    int SetSoundChannelVolume(int channel, int volume);

private:
    SoundManager() {}
    ~SoundManager() {}

    static SoundManager *instance;

    unordered_map<string, Mix_Music *> tracks;
    unordered_map<string, Mix_Chunk *> sounds;
};