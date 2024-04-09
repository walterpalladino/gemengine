
#include "core/physics/collider/Collider.h"

void Collider::Update(float time)
{
    if (!enabled)
        return;
}

SDL_Rect Collider::GetRect()
{
    SDL_Rect rect;

    rect.x = offset.x;
    rect.y = offset.y;
    rect.w = size.x;
    rect.h = size.y;

    return rect;
}

SDL_Rect Collider::GetRect(Transform transform)
{
    SDL_Rect rect;

    rect.x = transform.position.x + offset.x;
    rect.y = transform.position.y + offset.y;
    rect.w = size.x * abs(transform.scale.x);
    rect.h = size.y * abs(transform.scale.y);

    return rect;
}

void Collider::RenderCollider(SDL_Renderer *renderer, SDL_Color color, Transform transform)
{
    if (enabled)
    {
        //  Draw collider
        SDL_Rect rect = GetRect(transform);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void Collider::RenderCollisionRect(SDL_Renderer *renderer, uint64_t id, SDL_Color color)
{
    if (collisions.count(id) > 0)
    {
        //  Draw collision rect
        SDL_Rect collisionRect = collisions[id];
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(renderer, &collisionRect);
    }
}

void Collider::RenderCollisions(SDL_Renderer *renderer, SDL_Color color)
{
    if (enabled)
    {
        for (auto &[id, rect] : collisions)
        {
            RenderCollisionRect(renderer, id, color);
        }
    }
}
