#pragma once

#include <unordered_map>
// #include <vector>
#include <string>

#include <SDL2/SDL.h>

#include "core/GemObject.h"

using namespace std;

#define MAX_OBJECTS_PER_SCENE 65536

class Scene
{
private:
    // SDL_Renderer *renderer;

private:
    unordered_map<string, GemObject *> objects;

public:
    string name;
    //    vector<GemObject *> objects;

    // Scene(SDL_Renderer *renderer);
    Scene();
    ~Scene();

    GemObject *Add(const char *name, GemObject *object);

    GemObject *Get(const char *name);

    void Render(float time);

    void Cleanup();

    int Load(string fileName, SDL_Renderer *renderer, string resourceFolder);
};