#pragma once

#include <unordered_map>
#include <string>

#include <SDL2/SDL.h>

#include "core/gemobject/GemObject.h"

using namespace std;

class Scene
{

private:
    unordered_map<uint64_t, GemObject *> objects;

public:
    string name;

    Scene();
    ~Scene();

    GemObject *Add(GemObject *object);
    GemObject *GetByName(const string name);
    GemObject *GetById(const uint64_t id);

    void Update(float time);
    void Render(SDL_Renderer *renderer, float time);
    void Cleanup();

    int Load(string fileName, SDL_Renderer *renderer);

    const unordered_map<uint64_t, GemObject *> GetObjects()
    {
        return objects;
    }

    void OnMouseButtonDown(SDL_Event &event);
    void OnMouseButtonUp(SDL_Event &event);
    void OnMouseMove(SDL_Event &event);
};