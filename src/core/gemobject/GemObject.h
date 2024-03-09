#pragma once

#include <string>
#include <SDL2/SDL.h>

#include <nlohmann/json.hpp>

#include "math/Vector3d.h"

using json = nlohmann::json;

class GemObject
{

public:
    std::string name;

    bool enabled;

    Vector3d position = Vector3d::Zero();
    Vector3d rotation = Vector3d::Zero();
    Vector3d scale = Vector3d::One();

    int zOrder = 0;
    int layer = 0;

    virtual void Init() {}
    virtual void Update() {}
    virtual void Render(float time) {}
    virtual void Cleanup() {}

    virtual void JSONParse(json data);
};