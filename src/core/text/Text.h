#pragma once

#include <string>
#include <SDL2_ttf/SDL_ttf.h>

#include "core/Object.h"

using namespace std;

class Text : public Object
{
private:
    string text;
    string fontKey;

    SDL_Rect sourceRect;
    SDL_Rect destRect;
    SDL_Renderer *renderer;

public:
    Text(SDL_Renderer *renderer);
    ~Text();
    virtual void Init();
    virtual void Update();
    virtual void Cleanup();

    virtual void Render();

    void Set(const string, const char *fileName, const int fontSize);
};
