#pragma once

#include "core/scenes/SceneLogic.h"
#include "core/scenes/Scene.h"

class Scene2 : public SceneLogic
{
private:
    Scene *scene;

public:
    void Init(Scene *scene);
    Scene *Loop(float time);
    void Clean();
};