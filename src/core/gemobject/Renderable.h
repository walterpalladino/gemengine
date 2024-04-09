#pragma once

#include <SDL2/SDL.h>

class Renderable
{

protected:
    SDL_Renderer *renderer = NULL;

public:
    virtual void Init(SDL_Renderer *renderer) { this->renderer = renderer; };
    virtual void Render(float time) = 0;
};