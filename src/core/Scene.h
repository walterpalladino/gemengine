#pragma once

#include <vector>
#include <string>

#include <SDL2/SDL.h>

#include "core/Object.h"

using namespace std;

#define MAX_OBJECTS_PER_SCENE 65536

class Scene
{
private:
    SDL_Renderer *renderer;

public:
    string name;
    vector<Object *> objects;

    Scene(SDL_Renderer *renderer);
    ~Scene();

    void Render(float time);

    void Cleanup();
};