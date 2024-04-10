#pragma once

#include <string>

#include "core/gemobject/Component.h"

using namespace std;

class Track : public Component
{
private:
    string trackName;

public:
    ComponentType GetType()
    {
        return ComponentType::Track;
    }

    void SetName(string trackName)
    {
        this->trackName = trackName;
    }
    string GetName() { return trackName; }

    void Cleanup();

    void Play();
    void Stop();
};