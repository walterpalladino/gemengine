#pragma once

#include <string>
#include <unordered_map>

#include "core/scenes/Scene.h"
#include "core/scenes/SceneLogic.h"

using namespace std;

class SceneManager
{

public:
    static SceneManager *Instance()
    {
        if (instance == 0)
        {
            instance = new SceneManager();
        }
        return instance;
    }

private:
    SceneManager() {}
    ~SceneManager() {}

    static SceneManager *instance;

    unordered_map<string, SceneLogic *> sceneLogicMap;

    Scene *newScene;
    SceneLogic *activeSceneLogic;

public:
    virtual void LoadScenes(SDL_Renderer *renderer);
    Scene *GetScene(const string name);
    void Cleanup();
    void Loop(float time, bool isPaused);
    void UpdateActiveScene(float time);
    void RenderActiveScene(SDL_Renderer *renderer, float time);

    void AddSceneLogic(const string name, SceneLogic *sceneLogic);
    SceneLogic *GetActiveSceneLogic();

    bool ValidateScenesLogic();

    void OnMouseButtonDown(SDL_Event &event);
    void OnMouseButtonUp(SDL_Event &event);
    void OnMouseMove(SDL_Event &event);

public:
    vector<Scene *> scenes;
    Scene *activeScene;
};