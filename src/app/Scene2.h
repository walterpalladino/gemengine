#pragma once

#include "core/scenes/SceneLogic.h"
#include "core/scenes/Scene.h"
#include "core/graphics/parallax/Parallax.h"

class Scene2 : public SceneLogic
{
private:
    Scene *scene;

    Parallax *parallax_back;
    Parallax *parallax_middle;
    Parallax *parallax_lights;
    Parallax *parallax_front;

    int layer_middle_offset = 0;
    int layer_middle_speed = 0;

    int layer_lights_offset = 0;
    int layer_lights_speed = 0;

    int layer_front_offset = 0;
    int layer_front_speed = 0;

    float startTime = -1.0f;

public:
    void Init(Scene *scene);
    SceneTransition Loop(float time);
    void Clean();
};