#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "core/gemobject/Component.h"

using namespace std;

class Text : public Component
{
private:
    string text;
    TTF_Font *font;

    SDL_Rect sourceRect;
    SDL_Rect destRect;

public:
    Text();
    ~Text();

    virtual void Init();
    virtual void Update(float time);
    virtual void Cleanup();

    void Render(SDL_Renderer *renderer, Transform parentTransform, float time);

    void Init(const string, const char *fileName, const int fontSize);
    void SetText(string text) { this->text = text; }

    ComponentType GetType()
    {
        return ComponentType::Text;
    }
};
