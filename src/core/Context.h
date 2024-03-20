#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "core/gemobject/GemObject.h"

using namespace std;

class Context
{
public:
    static Context *Instance()
    {
        if (instance == 0)
        {
            instance = new Context();
        }
        return instance;
    }

private:
    Context() {}
    ~Context() {}

    static Context *instance;

public:
    unordered_map<string, GemObject *> objects;

    //  FPS Counter
    uint32_t firstRenderTick;
    uint32_t lastRenderTime;
    uint32_t startFrameTick;
    uint32_t endFrameTick;

    uint32_t lastFrameTime;

    float targetFPS = 60.0f;
    uint32_t targetFrameTime;
    double totalFrames;

    float GetFPS();
    uint32_t GetLastFrameTime()
    {
        return lastFrameTime;
    }
    void InitFPSCounter();
    float StartFPSFrameCounter();
    void WaitForEndFrame();
};