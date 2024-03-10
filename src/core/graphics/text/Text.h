#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "core/gemobject/GemObject.h"

using namespace std;

class Text : public GemObject
{
private:
    string text;
    TTF_Font *font;

    SDL_Rect sourceRect;
    SDL_Rect destRect;
    SDL_Renderer *renderer;

public:
    Text(SDL_Renderer *renderer);
    ~Text();
    virtual void Init();
    virtual void Update();
    virtual void Cleanup();

    virtual void Render(float time);

    void Init(const string, const char *fileName, const int fontSize);
    void SetText(string text) { this->text = text; }

    virtual void JSONParse(json data);
};
