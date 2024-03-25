#pragma once

#include <unordered_map>
#include <string>

#include <SDL2/SDL.h>

#include "core/gemobject/GemObject.h"

using namespace std;

class Scene
{

private:
    unordered_map<string, GemObject *> objects;

public:
    string name;

    Scene();
    ~Scene();

    GemObject *Add(const char *name, GemObject *object);
    GemObject *Get(const char *name);

    void Update(float time);
    void Render(float time);
    void Cleanup();

    int Load(string fileName, SDL_Renderer *renderer);

    const unordered_map<string, GemObject *> GetObjects()
    {
        return objects;
    }
};