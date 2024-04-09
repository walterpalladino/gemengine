#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>

#include <nlohmann/json.hpp>

#include "math/Vector3d.h"

#include "core/gemobject/Transform.h"
#include "core/gemobject/Component.h"
#include "core/physics/collider/Collider.h"

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
    uint64_t id;
    std::string name;

    bool enabled;

    Transform transform;

    unordered_map<ComponentType, vector<Component *>> components;

    int zOrder = 0;
    unsigned int layer = 1;

    GemObject();
    ~GemObject();

    void Init();
    void Update(float time);
    void Render(SDL_Renderer *renderer, float time);
    void Cleanup();

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

    //  Components
    void AddComponent(Component *component);
    void RemoveComponent(Component *component);
    void RemoveAllComponents();
    vector<Component *> GetComponentsByType(ComponentType type);
};