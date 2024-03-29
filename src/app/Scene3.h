#pragma once

#include "core/scenes/SceneLogic.h"

class Scene3 : public SceneLogic
{
private:
    Scene *scene;

public:
    void Init(Scene *scene);
    SceneTransition Loop(float time);
    void Clean();
};