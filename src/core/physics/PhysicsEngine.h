#pragma once

#include <vector>
#include <unordered_map>

#include "core/gemobject/GemObject.h"

using namespace std;

class PhysicsEngine
{
public:
    static void Physics(float time);
    static vector<GemObject *> GetColliderEnabledObjects(unordered_map<string, GemObject *> objects);
    static void DebugRender(SDL_Renderer *renderer, float time);
};
