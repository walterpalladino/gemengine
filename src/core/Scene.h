#pragma once

#include <vector>
#include <string>

#include <SDL2/SDL.h>

#include "core/GemObject.h"

using namespace std;

#define MAX_OBJECTS_PER_SCENE 65536

class Scene
{
private:
    // SDL_Renderer *renderer;

public:
    string name;
    vector<GemObject *> objects;

    // Scene(SDL_Renderer *renderer);
    Scene();
    ~Scene();

    void Render(float time);

    void Cleanup();
};