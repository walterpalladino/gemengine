#include "GemObject.h"

#include <iostream>
#include <random>

#include "core/config/Config.h"
#include "core/physics/collider/ColliderParser.h"

using namespace std;

GemObject::GemObject()
{
    //  Generate random id
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dis;

    id = dis(gen);
}

GemObject::~GemObject()
{
}

void GemObject::Init()
{
}

/*


SDL_Rect GemObject::GetColliderRect()
{
    return collider.GetRect(transform);
}

void GemObject::RenderCollider(SDL_Renderer *renderer, SDL_Color color)
{
    collider.RenderCollider(renderer, color, transform);
}

void GemObject::RenderCollisionRect(SDL_Renderer *renderer, uint64_t id, SDL_Color color)
{
    collider.RenderCollisionRect(renderer, id, color);
}
*/
void GemObject::AddOnMouseMoveEvent(SceneLogic *scene, EventCallbackFunction *callback)
{
    onMouseMoveSubscribers[scene] = callback;
}

void GemObject::AddOnMouseButtonDownEvent(SceneLogic *scene, EventCallbackFunction *callback)
{
    onMouseButtonDownSubscribers[scene] = callback;
}

void GemObject::AddOnMouseButtonUpEvent(SceneLogic *scene, EventCallbackFunction *callback)
{
    onMouseButtonUpSubscribers[scene] = callback;
}

void GemObject::RemoveOnMouseMoveEvent(SceneLogic *scene)
{
    onMouseMoveSubscribers.erase(scene);
}
void GemObject::RemoveOnMouseButtonDownEvent(SceneLogic *scene)
{
    onMouseButtonDownSubscribers.erase(scene);
}
void GemObject::RemoveOnMouseButtonUpEvent(SceneLogic *scene)
{
    onMouseButtonUpSubscribers.erase(scene);
}

void GemObject::OnMouseButtonDown(SDL_Event &event)
{
    // cout << "GemObject::OnMouseButtonDown for " << name << endl;

    // if (onMouseButtonDownSubscribers.size() > 0)
    // {
    //     //  Check if the mouse is over the object
    //     SDL_Rect rect = GetColliderRect();
    //     // cout << "rect : " << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << endl;

    //     SDL_Point mousePos = {event.button.x, event.button.y};
    //     SDL_FPoint scale = Config::Instance()->GetWindowScale();
    //     //        mousePos.x = mousePos.x * Config::Instance()->config_data.virtual_window_width / Config::Instance()->config_data.window_width;
    //     //        mousePos.y = mousePos.y * Config::Instance()->config_data.virtual_window_height / Config::Instance()->config_data.window_height;
    //     mousePos.x = mousePos.x * scale.x;
    //     mousePos.y = mousePos.y * scale.y;
    //     // cout << "mousePos : " << mousePos.x << " " << mousePos.y << endl;

    //     if (SDL_PointInRect(&mousePos, &rect) == SDL_FALSE)
    //     {
    //         return;
    //     }
    //     /*
    //             cout << "onMouseButtonDownSubscribers.size() : " << onMouseButtonDownSubscribers.size() << endl;

    //             cout << "GemObject::OnMouseButtonDown" << endl;
    //             cout << "name : " << name << endl;
    //             cout << "event.type : " << event.type << endl;
    //             cout << "event.button.button : " << event.button.button << endl;
    //             cout << "event.button.x : " << event.button.x << endl;
    //             cout << "event.button.y : " << event.button.y << endl;

    //             if (event.button.button == SDL_BUTTON_LEFT)
    //             {
    //                 cout << "Left Mouse Button Pressed." << endl;
    //             }
    //             else if (event.button.button == SDL_BUTTON_MIDDLE)
    //             {
    //                 cout << "Middle Mouse Button Pressed." << endl;
    //             }
    //             else if (event.button.button == SDL_BUTTON_RIGHT)
    //             {
    //                 cout << "Right Mouse Button Pressed." << endl;
    //             }
    //     */
    //     for (auto &[sceneLogic, callback] : onMouseButtonDownSubscribers)
    //     {
    //         // cout << "calling callback !!!" << endl;
    //         callback(this, &event);
    //     }
    // }
}

void GemObject::OnMouseButtonUp(SDL_Event &event)
{

    // if (onMouseButtonUpSubscribers.size() > 0)
    // {
    //     //  Check if the mouse is over the object
    //     SDL_Rect rect = GetColliderRect();

    //     SDL_Point mousePos = {event.button.x, event.button.y};
    //     SDL_FPoint scale = Config::Instance()->GetWindowScale();
    //     mousePos.x = mousePos.x * scale.x;
    //     mousePos.y = mousePos.y * scale.y;

    //     if (SDL_PointInRect(&mousePos, &rect) == SDL_FALSE)
    //     {
    //         return;
    //     }

    //     for (auto &[sceneLogic, callback] : onMouseButtonUpSubscribers)
    //     {
    //         callback(this, &event);
    //     }
    // }
}

void GemObject::OnMouseMove(SDL_Event &event)
{

    // if (onMouseMoveSubscribers.size() > 0)
    // {
    //     //  Check if the mouse is over the object
    //     SDL_Rect rect = GetColliderRect();

    //     SDL_Point mousePos = {event.button.x, event.button.y};
    //     SDL_FPoint scale = Config::Instance()->GetWindowScale();
    //     mousePos.x = mousePos.x * scale.x;
    //     mousePos.y = mousePos.y * scale.y;

    //     if (SDL_PointInRect(&mousePos, &rect) == SDL_FALSE)
    //     {
    //         return;
    //     }

    //     for (auto &[sceneLogic, callback] : onMouseMoveSubscribers)
    //     {
    //         callback(this, &event);
    //     }
    // }
}

void GemObject::AddComponent(Component *component)
{
    if (components.find(component->GetType()) == components.end())
    {
        components[component->GetType()] = vector<Component *>();
    }
    vector<Component *> componentsOfType = components.at(component->GetType());
    componentsOfType.push_back(component);
    components[component->GetType()] = componentsOfType;
}

void GemObject::RemoveComponent(Component *component)
{
}

void GemObject::RemoveAllComponents()
{
    for (auto &[key, value] : components)
    {
        for (auto component : value)
        {
            delete component;
        }
    }
    components.clear();
}

vector<Component *> GemObject::GetComponentsByType(ComponentType type)
{
    if (components.find(type) == components.end())
    {
        return vector<Component *>();
    }
    return components.at(type);
}

void GemObject::Render(SDL_Renderer *renderer, float time)
{

    if (!enabled)
    {
        return;
    }

    for (auto &[key, value] : components)
    {
        for (auto component : value)
        {
            component->Render(renderer, transform, time);
        }
    }
}

void GemObject::Update(float time)
{

    if (!enabled)
    {
        return;
    }

    for (auto &[key, value] : components)
    {
        for (auto component : value)
        {
            component->Update(time);
        }
    }
}

void GemObject::Cleanup()
{

    for (auto &[key, value] : components)
    {
        for (auto component : value)
        {
            component->Cleanup();
            delete component;
        }
    }
    components.clear();
}
