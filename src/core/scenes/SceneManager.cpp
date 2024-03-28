
#include "core/scenes/SceneManager.h"
#include "core/scenes/Scene.h"
#include "utils/Log.h"
#include "utils/StringUtils.h"
#include "core/config/Config.h"

SceneManager *SceneManager::instance = 0;

void SceneManager::LoadScenes(SDL_Renderer *renderer)
{
    Log::Instance()->Info("GemEngine::LoadScenes", "Load Scenes");

    string resourceFolder = Config::Instance()->config_data.resource_folder;

    for (auto &&scene_name : Config::Instance()->config_data.scenes)
    {
        Log::Instance()->Info("GemEngine::LoadScenes", "Loading Scene: %s", scene_name.c_str());

        //  Create & Load Scene
        Scene *newScene = new Scene();
        newScene->Load(StringPrintf("%s/%s", resourceFolder.c_str(), scene_name.c_str()).c_str(), renderer);
        // newScene->name = scene_name;

        //  Add Scene to Scenes list
        scenes.push_back(newScene);
    }

    activeScene = scenes.front();

    Log::Instance()->Info("GemEngine::LoadScenes", "Load Scenes Completed");
}

void SceneManager::Clean()
{
    Log::Instance()->Info("SceneManager::Clean", "SceneManager Shutting Down");

    //  Clean up scenes
    for (auto scene : scenes)
    {
        Log::Instance()->Info("GemEngine::~App", "Deleting scene: %s", scene->name.c_str());
        scene->Cleanup();
        delete scene;
    }
    scenes.clear();
}

Scene *SceneManager::GetScene(const string name)
{
    for (auto &&scene : scenes)
    {
        // cout << "Checking scene: " << scene->name << endl;
        if (scene->name == name)
        {
            // cout << "Found scene: " << name << endl;
            return scene;
        }
    }
    return NULL;
}

void SceneManager::RenderActiveScene(float time)
{
    activeScene->Render(time);
}

void SceneManager::UpdateActiveScene(float time)
{
    activeScene->Update(time);
}

void SceneManager::AddSceneLogic(const string sceneName, SceneLogic *sceneLogic)
{
    sceneLogicMap[sceneName] = sceneLogic;
}

SceneLogic *SceneManager::GetActiveSceneLogic()
{
    if (activeScene == NULL)
    {
        return NULL;
    }
    return sceneLogicMap[activeScene->name];
}

bool SceneManager::ValidateScenesLogic()
{

    for (auto &&scene : scenes)
    {

        if (sceneLogicMap.find(scene->name) == sceneLogicMap.end())
        {
            Log::Instance()->Error("SceneManager::ValidateScenesLogic", "SceneLogic not found: %s", scene->name.c_str());
            return false;
        }
    }

    return true;
}

void SceneManager::Loop(float time, bool isPaused)
{

    if (newScene == NULL)
    {
        newScene = activeScene;
        activeSceneLogic = GetActiveSceneLogic();
        if (activeScene != NULL)
        {
            activeSceneLogic->Init(activeScene);
        }
    }

    // Check if scene changed
    if ((newScene != NULL) && (activeScene != newScene))
    {
        // If switching to a new scene so first clean the actual one
        if (activeScene != NULL)
        {
            activeSceneLogic->Clean();
        }

        // Set the new scene
        activeScene = newScene;
        newScene = NULL;
        // cout << "Switching to scene: " << SceneManager::Instance()->activeScene->name << endl;
        activeSceneLogic = GetActiveSceneLogic();

        //  If it is a new scene then init the logic
        if (activeScene != NULL)
        {
            activeSceneLogic->Init(activeScene);
        }
    }

    // Logic loop
    if (activeSceneLogic != NULL)
    {
        // When paused do not update logic
        if (!isPaused)
        {
            SceneTransition newSceneTransition = activeSceneLogic->Loop(time);
            UpdateActiveScene(time);

            newScene = newSceneTransition.scene;
        }
    }
}

void SceneManager::OnMouseButtonDown(SDL_Event &event)
{
    if (activeScene != NULL)
    {
        activeScene->OnMouseButtonDown(event);
    }
}

void SceneManager::OnMouseButtonUp(SDL_Event &event)
{
    if (activeScene != NULL)
    {
        activeScene->OnMouseButtonUp(event);
    }
}

void SceneManager::OnMouseMove(SDL_Event &event)
{
    if (activeScene != NULL)
    {
        activeScene->OnMouseMove(event);
    }
}
