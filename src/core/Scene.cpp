#include <iostream>
#include <chrono>

#include "core/Scene.h"

#include "utils/Log.h"

#include "core/graphics/console/Console.h"

#include "core/exceptions/DuplicatedResourceIdentifier.h"

// Scene::Scene(SDL_Renderer *renderer)
Scene::Scene()
{
    Log::GetInstance()->Info("Scene::Scene", "Constructor");
    // this->renderer = renderer;
    // objects.reserve(MAX_OBJECTS_PER_SCENE);
}

Scene::~Scene()
{
    Log::GetInstance()->Info("Scene::~Scene", "Destructor");
}

GemObject *Scene::Add(const char *name, GemObject *object)
{
    //  Check if there is an object with the same name
    if (objects.count(name) != 0)
    {
        printf("Scene::Add - Duplicate Identifier %s\n", name);
        char *buffer = new char[512];
        sprintf(buffer, "Duplicate Identifier: %s.", name);

        Log::GetInstance()->Error("Scene::Add", buffer);
        throw DuplicatedResourceIdentifier(buffer);
    }

    objects[name] = object;
}

GemObject *Scene::Get(const char *name)
{
    return objects[name];
}

void Scene::Render(float time)
{

    Console::Instance()->Render(time);

    //  Render scene objects
    for (auto &[name, object] : objects)
    {
        object->Render(time);
    }
}

void Scene::Cleanup()
{
    Log::GetInstance()->Info("Scene::Cleanup", "Cleanup");

    //  Clean up scene objects
    for (auto &[name, object] : objects)
    {
        Log::GetInstance()->Info("Scene::Cleanup", "Deleting object: %s", object->name.c_str());
        object->Cleanup();
        delete object;
    }
    objects.clear();
}
