#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL2_mixer/SDL_mixer.h>

using namespace std;

#define MAX_SOUNDS_PER_APP 256
#define MAX_TRACKS_PER_APP 256

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
    void Clean();

    Mix_Music *AddTrack(string sampleFileName, int size);
    Mix_Chunk *AddSound(string sampleFileName, int size);

private:
    SoundManager() {}
    ~SoundManager() {}

    static SoundManager *instance;

    unordered_map<string, Mix_Music *> tracks;
    unordered_map<string, Mix_Chunk *> sounds;

    string GetTrackKey(string sampleFileName, int size);
    string GetSoundKey(string sampleFileName, int size);
};