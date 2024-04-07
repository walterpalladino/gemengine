#pragma once

#include <SDL2_image/SDL_image.h>

#include "core/gemobject/GemObject.h"
#include "math/Point2dInt.h"
#include "core/graphics/animation/Animation.h"
#include "core/graphics/textures/TextureManager.h"

class Sprite : public GemObject
{

private:
    SDL_Rect sourceRect;
    SDL_Rect destRect;
    SDL_Renderer *renderer;

    int actualAnimation = -1;
    vector<Animation> animations;

public:
    Sprite(SDL_Renderer *renderer);
    ~Sprite();

    virtual void Init();
    virtual void Update(float time);
    virtual void Cleanup();

    virtual void Render(float time);

    virtual void JSONParse(json data);

    void AddAnimation(Animation animation);
    Animation GetAnimation(int index);

    int GetActualAnimation();
    void SetActualAnimation(int actualAnimation);

    int GetAnimationsCount() { return animations.size(); }
};