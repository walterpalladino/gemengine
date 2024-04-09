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

void GemObject::JSONParse(json data)
{

    name = data["name"];
    enabled = data["enabled"];
    zOrder = data["z_order"];
    layer = data["layer"];

    json json_position = data.at("position");
    transform.position = Vector3d(json_position.at("x"), json_position.at("y"), json_position.at("z"));

    json json_rotation = data.at("rotation");
    transform.rotation = Vector3d(json_rotation.at("x"), json_rotation.at("y"), json_rotation.at("z"));

    json json_scale = data.at("scale");
    transform.scale = Vector3d(json_scale.at("x"), json_scale.at("y"), json_scale.at("z"));

    if (data.contains("collider"))
    {
        json json_collider = data.at("collider");

        collider = ColliderParser::JSONParse(json_collider);
    }
}

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

    if (onMouseButtonDownSubscribers.size() > 0)
    {
        //  Check if the mouse is over the object
        SDL_Rect rect = GetColliderRect();
        // cout << "rect : " << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << endl;

        SDL_Point mousePos = {event.button.x, event.button.y};
        SDL_FPoint scale = Config::Instance()->GetWindowScale();
        //        mousePos.x = mousePos.x * Config::Instance()->config_data.virtual_window_width / Config::Instance()->config_data.window_width;
        //        mousePos.y = mousePos.y * Config::Instance()->config_data.virtual_window_height / Config::Instance()->config_data.window_height;
        mousePos.x = mousePos.x * scale.x;
        mousePos.y = mousePos.y * scale.y;
        // cout << "mousePos : " << mousePos.x << " " << mousePos.y << endl;

        if (SDL_PointInRect(&mousePos, &rect) == SDL_FALSE)
        {
            return;
        }
        /*
                cout << "onMouseButtonDownSubscribers.size() : " << onMouseButtonDownSubscribers.size() << endl;

                cout << "GemObject::OnMouseButtonDown" << endl;
                cout << "name : " << name << endl;
                cout << "event.type : " << event.type << endl;
                cout << "event.button.button : " << event.button.button << endl;
                cout << "event.button.x : " << event.button.x << endl;
                cout << "event.button.y : " << event.button.y << endl;

                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    cout << "Left Mouse Button Pressed." << endl;
                }
                else if (event.button.button == SDL_BUTTON_MIDDLE)
                {
                    cout << "Middle Mouse Button Pressed." << endl;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    cout << "Right Mouse Button Pressed." << endl;
                }
        */
        for (auto &[sceneLogic, callback] : onMouseButtonDownSubscribers)
        {
            // cout << "calling callback !!!" << endl;
            callback(this, &event);
        }
    }
}

void GemObject::OnMouseButtonUp(SDL_Event &event)
{

    if (onMouseButtonUpSubscribers.size() > 0)
    {
        //  Check if the mouse is over the object
        SDL_Rect rect = GetColliderRect();

        SDL_Point mousePos = {event.button.x, event.button.y};
        SDL_FPoint scale = Config::Instance()->GetWindowScale();
        mousePos.x = mousePos.x * scale.x;
        mousePos.y = mousePos.y * scale.y;

        if (SDL_PointInRect(&mousePos, &rect) == SDL_FALSE)
        {
            return;
        }

        for (auto &[sceneLogic, callback] : onMouseButtonUpSubscribers)
        {
            callback(this, &event);
        }
    }
}

void GemObject::OnMouseMove(SDL_Event &event)
{

    if (onMouseMoveSubscribers.size() > 0)
    {
        //  Check if the mouse is over the object
        SDL_Rect rect = GetColliderRect();

        SDL_Point mousePos = {event.button.x, event.button.y};
        SDL_FPoint scale = Config::Instance()->GetWindowScale();
        mousePos.x = mousePos.x * scale.x;
        mousePos.y = mousePos.y * scale.y;

        if (SDL_PointInRect(&mousePos, &rect) == SDL_FALSE)
        {
            return;
        }

        for (auto &[sceneLogic, callback] : onMouseMoveSubscribers)
        {
            callback(this, &event);
        }
    }
}