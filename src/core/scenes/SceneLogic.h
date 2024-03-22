#pragma once

#include "core/scenes/Scene.h"
#include "core/scenes/SceneTransition.h"

class SceneLogic
{
public:
    virtual void Init(Scene *scene) = 0;
    virtual SceneTransition Loop(float time) = 0;
    virtual void Clean() = 0;
};