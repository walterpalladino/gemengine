#pragma once

#include <vector>
#include <chrono>

#include <SDL2/SDL.h>

#include "core/Scene.h"

using namespace std;

#define MAX_SCENES_PER_APP 1024

class App
{
protected:
    bool Running = true;

    SDL_Window *Window = NULL;
    SDL_Renderer *Renderer = NULL;

    int WindowWidth = 1024;
    int WindowHeight = 768;

    vector<Scene *> scenes;
    Scene *activeScene;

    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point lastTimeOfLoop;

    double totalFrames;

protected:
    App();
    ~App();

    // Capture SDL Events
    void OnEvent(SDL_Event *Event);

    // Initialize our SDL game / app
    bool Init();

    // Physics loop
    void Physics();

    // Poll Events
    void PollEvents();

    // Render loop (draw)
    void Render();

    // Free up resources
    void Cleanup();

protected:
    // Logic loop
    virtual void Loop(float time) {}
    virtual void LoadScenes() {}

public:
    int Execute(int argc, char *argv[]);

    int GetWindowWidth() { return WindowWidth; }
    int GetWindowHeight() { return WindowHeight; }
};
