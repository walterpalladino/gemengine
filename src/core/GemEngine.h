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
    bool pausedPressed = false;

    SDL_Renderer *renderer = NULL;

protected:
    // Capture SDL Events
    void OnEvent(SDL_Event *Event);

    // Poll Events
    void PollEvents();

private:
    // Timer
    SDL_TimerID processTimer;
    Uint32 ProcessTimer(Uint32 interval);
    static Uint32 ProcessTimerCallback(Uint32 interval, void *param);

protected:
    // Logic loop
    virtual void LoopInit() {}
    virtual Scene *Loop(float time) {}
    // Render loop (draw)
    virtual void Render(float time);

public:
    GemEngine(string resourceFolder);
    ~GemEngine();

    // Free up resources
    void Cleanup();

    int Start();
};
