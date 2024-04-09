#pragma once

#include <SDL2_image/SDL_image.h>

#include "core/gemobject/Component.h"
#include "core/gemobject/Transform.h"

#include "math/Point2dInt.h"

class Parallax : public Component
{

private:
    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect destRect;

public:
    Parallax();
    ~Parallax();

    virtual void Init();
    virtual void Update(float time);
    virtual void Cleanup();

    void SetTexture(SDL_Texture *texture);
    SDL_Texture *GetTexture();

    void Render(SDL_Renderer *renderer, Transform parentTransform, float time);

    Point2dInt offset = Point2dInt(0, 0);

    ComponentType GetType() { return ComponentType::Parallax; }
};