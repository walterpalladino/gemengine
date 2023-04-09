#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "core/Scene.h"
#include "math/Point2dInt.h"

using namespace std;

#define MAX_SCENES_PER_APP 1024

class GemEngine
{
protected:
    bool Running = true;

    SDL_Window *Window = NULL;
    SDL_Renderer *Renderer = NULL;

    SDL_Texture *virtualWindowTexture = NULL;
    SDL_Texture *windowTexture = NULL;

    Point2dInt windowSize = Point2dInt(1024, 768);

    Point2dInt virtualWindowSize = Point2dInt(384, 216);

    vector<Scene *> scenes;
    Scene *activeScene;

    uint32_t firstRenderTime;
    uint32_t lastRenderTime;

    float targetFPS = 60.0f;
    double totalFrames;

    int scaleQuality = 1;

protected:
    GemEngine();
    ~GemEngine();

    // Capture SDL Events
    void OnEvent(SDL_Event *Event);

    // Initialize our SDL game / app
    bool Init();

    // Physics loop
    void Physics();

    // Poll Events
    void PollEvents();

    // Render loop (draw)
    void Render(float time);

    // Free up resources
    void Cleanup();

    float GetFPS();

protected:
    // Logic loop
    virtual void Loop(float time) {}
    virtual void LoadScenes() {}

public:
    int Execute(int argc, char *argv[]);

    Point2dInt GetWindowSize() { return windowSize; }
};
