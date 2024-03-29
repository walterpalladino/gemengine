#pragma once

#include "core/scenes/SceneLogic.h"

#include "core/graphics/image/Image.h"
#include "core/graphics/sprites/Sprite.h"
#include "core/graphics/text/Text.h"

class Scene1 : public SceneLogic
{
private:
    Scene *scene;
    int sound_channel = 0;

    Image *ledArrow;
    Text *fpsText;
    Sprite *spriteWalk;
    Sprite *spriteIdle;

public:
    void Init(Scene *scene);
    SceneTransition Loop(float time);
    void Clean();

    static void OnMouseButtonDown(GemObject *gemObject, SDL_Event *event);
    static void OnMouseButtonUp(GemObject *gemObject, SDL_Event *event);
    static void OnMouseMove(GemObject *gemObject, SDL_Event *event);
};