#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "core/scenes/Scene.h"
#include "math/Point2dInt.h"
#include "math/Point3dInt.h"
#include "core/events/EventManager.h"

using namespace std;

class GemEngine
{
private:
    EventManagerStatus engineStatus = {true, false};

    SDL_Renderer *renderer = NULL;

private:
    // Timer
    SDL_TimerID processTimer;
    Uint32 ProcessTimer(Uint32 interval);
    static Uint32 ProcessTimerCallback(Uint32 interval, void *param);

    void Init();

    // Free up resources
    void Cleanup();

    // Render loop (draw)
    virtual void Render(float time);

public:
    GemEngine(string resourceFolder);
    ~GemEngine();

    int Start();
};
