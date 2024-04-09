#pragma once

#include <SDL2/SDL.h>

#include "core/gemobject/Transform.h"

enum class ComponentType : int
{
    Image = 1,
    Text = 2,
    Sprite = 3,
    Parallax = 4,
    Sound = 5,
    Collider = 6
};

class Component
{
public:
    bool enabled = true;

public:
    Component() {}
    ~Component() {}

    virtual ComponentType GetType() = 0;
    virtual void Update(float time) = 0;

    virtual void Render(SDL_Renderer *renderer, Transform parentTransform, float time) {}
};
