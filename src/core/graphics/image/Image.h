#pragma once

#include <SDL2_image/SDL_image.h>

#include "core/Object.h"

class Image : public Object
{

private:
    SDL_Texture *image;
    SDL_Rect sourceRect;
    SDL_Rect destRect;
    SDL_Renderer *renderer;

public:
    Image(SDL_Renderer *renderer);
    ~Image();
    virtual void Init();
    virtual void Update();
    virtual void Cleanup();

    virtual void Render(float time);

    void Load(const char *fileName);
};