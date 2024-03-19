#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "core/scenes/Scene.h"
#include "math/Point2dInt.h"
#include "math/Point3dInt.h"

using namespace std;

class GemEngine
{
protected:
    bool Running = true;

    SDL_Renderer *renderer = NULL;

    uint32_t firstRenderTick;
    uint32_t lastRenderTime;
    uint32_t startFrameTick;
    uint32_t endFrameTick;

    uint32_t lastFrameTime;

    float targetFPS = 60.0f;
    double totalFrames;

protected:
    GemEngine(string resourceFolder);
    ~GemEngine();

    // Capture SDL Events
    void OnEvent(SDL_Event *Event);

    // Poll Events
    void PollEvents();

    float GetFPS();
    uint32_t GetLastFrameTime()
    {
        return lastFrameTime;
    }

protected:
    // Logic loop
    virtual void LoopInit() {}
    virtual Scene *Loop(float time) {}
    // Render loop (draw)
    virtual void Render(float time);

public:
    // Free up resources
    void Cleanup();

    int Start();
};
