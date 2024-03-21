#include "Scene2.h"

#include "utils/Log.h"
#include "core/input/InputHandler.h"
#include "core/Config.h"
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"
#include "core/renderer/RenderManager.h"
#include "core/Context.h"

void Scene2::Init(Scene *scene)
{
    cout << "Scene2::Init" << endl;

    this->scene = scene;

    parallax = (Parallax *)(scene->Get("fantasy-world"));
}

Scene *Scene2::Loop(float time)
{

    //  Parallax Offset
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
    {
        parallax->offset.x -= 1;
    }
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
    {
        parallax->offset.x += 1;
    }
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP))
    {
        parallax->offset.y -= 1;
    }
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
    {
        parallax->offset.y += 1;
    }

    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_N))
    {
        //  Next Scene
        string newSceneName = "Third Scene";
        // cout << "Next Scene : " << newSceneName << endl;
        return SceneManager::Instance()->GetScene(newSceneName);
    }
    return scene;
}

void Scene2::Clean()
{
    cout << "Scene2::Clean" << endl;
}