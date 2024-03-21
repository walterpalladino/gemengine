#pragma once

#include "core/scenes/SceneLogic.h"
#include "core/scenes/Scene.h"
#include "core/graphics/parallax/Parallax.h"

class Scene2 : public SceneLogic
{
private:
    Scene *scene;
    Parallax *parallax;

public:
    void Init(Scene *scene);
    Scene *Loop(float time);
    void Clean();
};