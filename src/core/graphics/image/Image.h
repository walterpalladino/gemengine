#pragma once

#include <SDL2_image/SDL_image.h>

#include "core/gemobject/Component.h"
#include "core/gemobject/Transform.h"

class Image : public Component
{

private:
    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect destRect;

public:
    Image();
    ~Image();

    virtual void Init();
    virtual void Update(float time);
    virtual void Cleanup();

    void SetTexture(SDL_Texture *texture);
    SDL_Texture *GetTexture();

    void Render(SDL_Renderer *renderer, Transform parentTransform, float time);

    ComponentType GetType()
    {
        return ComponentType::Image;
    }
};