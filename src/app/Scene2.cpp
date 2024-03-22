#include "app/Scene2.h"

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

    parallax_back = (Parallax *)(scene->Get("parallax-forest-back-trees"));
    parallax_middle = (Parallax *)(scene->Get("parallax-forest-middle-trees"));
    parallax_lights = (Parallax *)(scene->Get("parallax-forest-lights"));
    parallax_front = (Parallax *)(scene->Get("parallax-forest-front-trees"));

    layer_middle_offset = 0;
    layer_middle_speed = 10;

    layer_lights_offset = 0;
    layer_lights_speed = -2;

    layer_front_offset = 0;
    layer_front_speed = 20;
}

Scene *Scene2::Loop(float time)
{

    if (startTime < 0)
    {
        startTime = time;
    }

    layer_middle_offset = (time - startTime) * layer_middle_speed / 1000;
    parallax_middle->offset.x = layer_middle_offset;

    layer_lights_offset = (time - startTime) * layer_lights_speed / 1000;
    parallax_lights->offset.x = layer_lights_offset;

    layer_front_offset = (time - startTime) * layer_front_speed / 1000;
    parallax_front->offset.x = layer_front_offset;

    /*
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
    */

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