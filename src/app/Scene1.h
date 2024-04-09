#pragma once

#include "core/scenes/SceneLogic.h"

#include "core/gemobject/GemObject.h"
#include "core/graphics/image/Image.h"
#include "core/graphics/sprites/Sprite.h"
#include "core/graphics/text/Text.h"
#include "core/physics/collider/Collider.h"

class Scene1 : public SceneLogic
{
private:
    Scene *scene;
    int sound_channel = 0;

    GemObject *ledArrow;

    GemObject *knight;
    Sprite *knightSprite;
    Collider *knightCollider;

    GemObject *text;
    Text *fpsText;

public:
    void Init(Scene *scene);
    SceneTransition Loop(float time);
    void Clean();

    static void OnMouseButtonDown(GemObject *gemObject, SDL_Event *event);
    static void OnMouseButtonUp(GemObject *gemObject, SDL_Event *event);
    static void OnMouseMove(GemObject *gemObject, SDL_Event *event);
};