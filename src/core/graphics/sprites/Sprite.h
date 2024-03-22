#pragma once

#include <SDL2_image/SDL_image.h>

#include "core/gemobject/GemObject.h"
#include "math/Point2dInt.h"

class Sprite : public GemObject
{

private:
    SDL_Texture *image;
    SDL_Rect sourceRect;
    SDL_Rect destRect;
    SDL_Renderer *renderer;

    Point2dInt offset = Point2dInt(0, 0);
    Point2dInt size = Point2dInt(0, 0);
    int animationFrames = 0;
    int animationSpeed = 30; // FPS

    int actualFrame;
    int animationStartTime;

public:
    Sprite(SDL_Renderer *renderer);
    ~Sprite();
    virtual void Init();
    virtual void Update(float time);
    virtual void Cleanup();

    virtual void Render(float time);

    void Load(const char *fileName, int offsetX, int offsetY, int width, int height, int frames, int speed);

    virtual void JSONParse(json data);
};