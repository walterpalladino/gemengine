#pragma once

#include "core/scenes/Scene.h"

struct SceneTransition
{
    Scene *scene;
    bool isTransitioning = false;
    bool isDone = false;
    bool isPaused = false;
};