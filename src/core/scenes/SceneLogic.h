#pragma once

#include "core/scenes/Scene.h"

class SceneLogic
{
public:
    virtual void Init(Scene *scene) = 0;
    virtual Scene *Loop(float time) = 0;
    virtual void Clean() = 0;
};