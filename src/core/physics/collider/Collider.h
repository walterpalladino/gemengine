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

private:
    bool renderCollider = false;
    bool renderCollisions = false;

private:
    void RenderCollider(SDL_Renderer *renderer, SDL_Color color, Transform transform);
    void RenderCollisionRect(SDL_Renderer *renderer, uint64_t id, SDL_Color color);
    void RenderCollisions(SDL_Renderer *renderer, SDL_Color color);

public:
    Vector3d offset = Vector3d::Zero();
    Vector3d size = Vector3d::Zero();

    unsigned int mask = UINT_MAX;

    unordered_map<uint64_t, SDL_Rect> collisions;

public:
    ComponentType GetType() { return ComponentType::Collider; }

    void Update(float time);
    void Render(SDL_Renderer *renderer, Transform parentTransform, float time);
    void Cleanup();

    SDL_Rect GetRect();
    SDL_Rect GetRect(Transform transform);

    void SetRenderCollider(bool value) { renderCollider = value; }
    void SetRenderCollisions(bool value) { renderCollisions = value; }
};
