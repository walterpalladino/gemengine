#pragma once

#include <SDL2_image/SDL_image.h>

#include "core/gemobject/Component.h"
#include "math/Point2dInt.h"
#include "core/graphics/animation/Animation.h"
#include "core/graphics/textures/TextureManager.h"

class Sprite : public Component
{

private:
    SDL_Rect sourceRect;
    SDL_Rect destRect;

    int actualAnimation = -1;
    vector<Animation> animations;

public:
    Sprite();
    ~Sprite();

    virtual void Init();
    virtual void Update(float time);
    virtual void Cleanup();

    void Render(SDL_Renderer *renderer, Transform parentTransform, float time);

    void AddAnimation(Animation animation);
    Animation GetAnimation(int index);

    int GetActualAnimation();
    void SetActualAnimation(int actualAnimation);

    int GetAnimationsCount() { return animations.size(); }

    ComponentType GetType()
    {
        return ComponentType::Sprite;
    }
};