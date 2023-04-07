#pragma once

#include <SDL2_image/SDL_image.h>

#include "core/Object.h"
#include "math/Point2dInt.h"

class Sprite : public Object
{

private:
    SDL_Texture *image;
    SDL_Rect sourceRect;
    SDL_Rect destRect;
    SDL_Renderer *renderer;

    Point2dInt size = Point2dInt(0, 0);
    int frames = 0;
    int animationSpeed = 30; // FPS

public:
    Sprite(SDL_Renderer *renderer);
    ~Sprite();
    virtual void Init();
    virtual void Update();
    virtual void Cleanup();

    virtual void Render();

    void Load(const char *fileName);
};