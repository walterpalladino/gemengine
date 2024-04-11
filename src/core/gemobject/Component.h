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
    Track = 6,
    Collider = 7
};

class Component
{
public:
    bool enabled = true;

public:
    Component() {}
    virtual ~Component(){};

    virtual ComponentType GetType() = 0;
    virtual void Update(float time){};
    virtual void Cleanup() = 0;

    virtual void Render(SDL_Renderer *renderer, Transform parentTransform, float time) {}
};
