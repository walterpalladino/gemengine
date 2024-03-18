#include "GemObject.h"

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