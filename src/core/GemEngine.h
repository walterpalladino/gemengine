#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "core/scenes/Scene.h"
#include "math/Point2dInt.h"
#include "math/Point3dInt.h"

using namespace std;

// #define MAX_SCENES_PER_APP 1024

class GemEngine
{
protected:
    bool Running = true;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Texture *virtualWindowTexture = NULL;
    SDL_Texture *windowTexture = NULL;

    Point2dInt windowSize = Point2dInt(1280, 720);

    // Virtual Screen Dimensions (pixels)
    Point2dInt virtualWindowSize = Point2dInt(384, 216);

    uint32_t firstRenderTick;
    uint32_t lastRenderTime;
    uint32_t startFrameTick;
    uint32_t endFrameTick;

    uint32_t lastFrameTime;

    float targetFPS = 60.0f;
    double totalFrames;

    int scaleQuality = 0;
    bool renderToVirtualWindow = true;

    Point3dInt backgroundColor;

private:
    void PreRender(float time);
    void PostRender(float time);

protected:
    GemEngine(string resourceFolder);
    ~GemEngine();

    // Capture SDL Events
    void OnEvent(SDL_Event *Event);

    // Initialize our SDL game / app
    bool Init();

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

    // int Start(int windowWidth, int windowHeight);
    // int Start(int windowWidth, int windowHeight, int virtualWindowWidth, int virtualWindowHeight);
    int Start();

    Point2dInt GetWindowSize() { return windowSize; }
};
