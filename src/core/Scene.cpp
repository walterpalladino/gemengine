#include <iostream>
#include <chrono>

#include "core/Scene.h"

#include "utils/Log.h"

// Scene::Scene(SDL_Renderer *renderer)
Scene::Scene()
{
    Log::GetInstance()->Info("Scene::Scene", "Constructor");
    // this->renderer = renderer;
    objects.reserve(MAX_OBJECTS_PER_SCENE);
}

Scene::~Scene()
{
    Log::GetInstance()->Info("Scene::~Scene", "Destructor");
}

void Scene::Render(float time)
{

    // SDL_RenderClear(renderer);

    // renderizar imagenes, etc.
    // SDL_RenderCopy(_renderer, _logoTexture, &_sourceLogoRect, &_destLogoRect);
    // SDL_RenderCopyEx(_renderer, _heroTexture, &_sourceHeroRect, &_destHeroRect, 0, NULL, SDL_FLIP_NONE);

    //  Clean up objects
    for (auto object : objects)
    {
        object->Render(time);
    }

    // Triggers the double buffers
    // SDL_RenderPresent(renderer);
}

void Scene::Cleanup()
{
    Log::GetInstance()->Info("Scene::Cleanup", "Cleanup");

    //  Clean up objects
    for (auto object : objects)
    {
        Log::GetInstance()->Info("Scene::Cleanup", "Deleting object: %s", object->name.c_str());
        object->Cleanup();
        delete object;
    }
    objects.clear();
}
