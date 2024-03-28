#include "GemObject.h"

#include <iostream>
#include "core/config/Config.h"

using namespace std;

void GemObject::JSONParse(json data)
{

    name = data["name"];
    enabled = data["enabled"];
    zOrder = data["z_order"];
    layer = data["layer"];

    json json_position = data.at("position");
    position = Vector3d(json_position.at("x"), json_position.at("y"), json_position.at("z"));

    json json_rotation = data.at("rotation");
    rotation = Vector3d(json_rotation.at("x"), json_rotation.at("y"), json_rotation.at("z"));

    json json_scale = data.at("scale");
    scale = Vector3d(json_scale.at("x"), json_scale.at("y"), json_scale.at("z"));

    if (data.contains("collider"))
    {
        json json_collider = data.at("collider");

        colliderEnabled = json_collider.at("enabled");
        colliderOffset = Vector3d(json_collider.at("offset").at("x"), json_collider.at("offset").at("y"), json_collider.at("offset").at("z"));
        colliderSize = Vector3d(json_collider.at("size").at("x"), json_collider.at("size").at("y"), json_collider.at("size").at("z"));
        colliderMask = json_collider.at("mask");
    }
}

SDL_Rect GemObject::GetColliderRect()
{
    SDL_Rect colliderRect;

    colliderRect.x = position.x + colliderOffset.x;
    colliderRect.y = position.y + colliderOffset.y;
    colliderRect.w = colliderSize.x * abs(scale.x);
    colliderRect.h = colliderSize.y * abs(scale.y);

    return colliderRect;
}

void GemObject::RenderCollider(SDL_Renderer *renderer, SDL_Color color)
{
    if (colliderEnabled)
    {
        //  Draw collider
        SDL_Rect colliderRect = GetColliderRect();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(renderer, &colliderRect);
    }
}

void GemObject::RenderCollisionRect(SDL_Renderer *renderer, string name, SDL_Color color)
{
    if (collisions.count(name) > 0)
    {
        SDL_Rect collisionRect = collisions[name];
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(renderer, &collisionRect);
    }
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