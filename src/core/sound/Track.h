#pragma once

#include <string>
#include <SDL2_mixer/SDL_mixer.h>

#include "core/gemobject/Component.h"

using namespace std;

class Track : public Component
{
private:
    string trackName;
    Mix_Music *track = NULL;

public:
    Track(string trackName, Mix_Music *track) : trackName(trackName), track(track) {}
    ComponentType GetType() { return ComponentType::Track; }

    string GetName() { return trackName; }
    Mix_Music *GetTrack() { return track; }

    void Cleanup();

    void Play();
    void Stop();

    int SetVolume(int volume);
};