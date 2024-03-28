#pragma once

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

#include <nlohmann/json.hpp>

#include "math/Vector3d.h"

using namespace std;
using json = nlohmann::json;

class SceneLogic;
class GemObject;

typedef void(EventCallbackFunction)(GemObject *, SDL_Event *);

class GemObject
{

private:
    //  Events
    unordered_map<SceneLogic *, EventCallbackFunction *> onMouseMoveSubscribers;
    unordered_map<SceneLogic *, EventCallbackFunction *> onMouseButtonDownSubscribers;
    unordered_map<SceneLogic *, EventCallbackFunction *> onMouseButtonUpSubscribers;

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
    void AddOnMouseMoveEvent(SceneLogic *scene, EventCallbackFunction *callback);
    void AddOnMouseButtonDownEvent(SceneLogic *scene, EventCallbackFunction *callback);
    void AddOnMouseButtonUpEvent(SceneLogic *scene, EventCallbackFunction *callback);

    void RemoveOnMouseMoveEvent(SceneLogic *scene);
    void RemoveOnMouseButtonDownEvent(SceneLogic *scene);
    void RemoveOnMouseButtonUpEvent(SceneLogic *scene);

    void OnMouseButtonDown(SDL_Event &event);
    void OnMouseButtonUp(SDL_Event &event);
    void OnMouseMove(SDL_Event &event);
};