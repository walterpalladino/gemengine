#pragma once

#include <string>
#include <SDL2/SDL.h>

#include <nlohmann/json.hpp>

#include "math/Vector3d.h"
#include <unordered_map>

using namespace std;
using json = nlohmann::json;

class GemObject
{

public:
    std::string name;

    bool enabled;

    Vector3d position = Vector3d::Zero();
    Vector3d rotation = Vector3d::Zero();
    Vector3d scale = Vector3d::One();

    bool colliderEnabled;

    Vector3d colliderOffset = Vector3d::Zero();
    Vector3d colliderSize = Vector3d::Zero();

    unsigned int colliderMask = 0;

    unordered_map<std::string, SDL_Rect> collisions;

    int zOrder = 0;
    int layer = 0;

    virtual void Init() {}
    virtual void Update(float time) {}
    virtual void Render(float time) {}
    virtual void Cleanup() {}

    virtual void JSONParse(json data);

    SDL_Rect GetColliderRect();
    void RenderCollider(SDL_Renderer *renderer, SDL_Color color);
    void RenderCollisionRect(SDL_Renderer *renderer, string name, SDL_Color color);

    //  Events
    // virtual void OnCollide(GemObject *collider) {}
    virtual void OnMouseOver(SDL_Event *event) {}
    virtual void OnMouseClick(SDL_Event *event) {}
    virtual void OnMouseRelease(SDL_Event *event) {}
};