#pragma once

#include <unordered_map>

#include <SDL2/SDL.h>

#include <nlohmann/json.hpp>

#include "math/Vector3d.h"

#include "core/gemobject/Component.h"

#include "core/gemobject/Transform.h"

using namespace std;
using json = nlohmann::json;

class Collider : public Component
{

public:
    Vector3d offset = Vector3d::Zero();
    Vector3d size = Vector3d::Zero();

    unsigned int mask = UINT_MAX;

    unordered_map<uint64_t, SDL_Rect> collisions;

public:
    ComponentType GetType() { return ComponentType::Collider; }

    void Update(float time);

    SDL_Rect GetRect();
    SDL_Rect GetRect(Transform transform);
    void RenderCollider(SDL_Renderer *renderer, SDL_Color color, Transform transform);
    void RenderCollisionRect(SDL_Renderer *renderer, uint64_t id, SDL_Color color);
    void RenderCollisions(SDL_Renderer *renderer, SDL_Color color);
};
