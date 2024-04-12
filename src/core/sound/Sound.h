#pragma once

#include <string>
#include <SDL2_mixer/SDL_mixer.h>

#include "core/gemobject/Component.h"

using namespace std;

class Sound : public Component
{
private:
    string soundName;
    Mix_Chunk *sound = NULL;
    int channel = -1;

public:
    Sound(string soundName, Mix_Chunk *sound) : soundName(soundName), sound(sound) {}
    ComponentType GetType() { return ComponentType::Sound; }

    string GetName() { return soundName; }
    Mix_Chunk *GetSound() { return sound; }

    void Cleanup();

    void Play(int loops = 0);
    void Stop();

    int SetVolume(int volume);
};