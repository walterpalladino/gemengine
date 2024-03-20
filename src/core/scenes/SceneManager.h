#pragma once

#include <string>
#include <unordered_map>
#include <vector>

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

    vector<GemObject *> GetColliderEnabledObjects(unordered_map<string, GemObject *> objects);

    unordered_map<string, SceneLogic *> sceneLogicMap;

public:
    virtual void LoadScenes(SDL_Renderer *renderer);
    Scene *GetScene(const string name);
    void Clean();
    // Physics loop
    void Physics(float time);
    void DebugRender(SDL_Renderer *renderer, float time);
    void RenderActiveScene(float time);

    void AddSceneLogic(const string name, SceneLogic *sceneLogic);
    SceneLogic *GetActiveSceneLogic();

public:
    vector<Scene *> scenes;
    Scene *activeScene;
};