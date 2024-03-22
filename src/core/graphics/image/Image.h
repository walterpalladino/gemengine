#pragma once

#include <SDL2_image/SDL_image.h>

#include "core/gemobject/GemObject.h"

class Image : public GemObject
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
    virtual void Update(float time);
    virtual void Cleanup();

    virtual void Render(float time);

    void Load(const char *fileName);

    virtual void JSONParse(json data);
};