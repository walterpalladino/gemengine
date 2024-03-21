#pragma once

#include "core/scenes/SceneLogic.h"
#include "core/scenes/Scene.h"
#include "core/graphics/parallax/Parallax.h"

class Scene2 : public SceneLogic
{
private:
    Scene *scene;
    Parallax *parallax;

    int layer_0_offset = 0;
    int layer_0_speed = 0;
    float startTime = -1.0f;

public:
    void Init(Scene *scene);
    Scene *Loop(float time);
    void Clean();
};