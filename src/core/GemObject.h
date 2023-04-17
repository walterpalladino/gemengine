#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "math/Vector3d.h"

class GemObject
{

public:
    std::string name;

    bool enabled;

    Vector3d position = Vector3d::Zero();
    Vector3d rotation = Vector3d::Zero();
    Vector3d scale = Vector3d::One();

    virtual void Init() {}
    virtual void Update() {}
    virtual void Render(float time) {}
    virtual void Cleanup() {}

    // void SetPosition(Vector3d position) { this->position = position; }
};