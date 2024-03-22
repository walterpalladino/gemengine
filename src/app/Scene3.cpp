#include "app/Scene3.h"

#include "utils/Log.h"
#include "core/input/InputHandler.h"
#include "core/Config.h"
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"
#include "core/renderer/RenderManager.h"
#include "core/Context.h"

void Scene3::Init(Scene *scene)
{
    cout << "Scene3::Init" << endl;

    this->scene = scene;
}

Scene *Scene3::Loop(float time)
{
    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_N))
    {
        //  Next Scene
        string newSceneName = "Start Scene";
        // cout << "Next Scene : " << newSceneName << endl;
        return SceneManager::Instance()->GetScene(newSceneName);
    }
    return scene;
}

void Scene3::Clean()
{
    cout << "Scene3::Clean" << endl;
}