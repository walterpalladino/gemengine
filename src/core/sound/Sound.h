#pragma once

#include <string>

#include "core/gemobject/Component.h"

using namespace std;

class Sound : public Component
{
private:
    string soundName;
    int channel = -1;

public:
    ComponentType GetType()
    {
        return ComponentType::Sound;
    }

    void SetName(string soundName)
    {
        this->soundName = soundName;
    }
    string GetName() { return soundName; }

    void Cleanup();

    void Play(int loops = 0);
    void Stop();

    int SetVolume(int volume);
};