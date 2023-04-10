#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "core/GemObject.h"
#include "math/Point2dInt.h"

class Console
{
public:
    static Console *Instance()
    {
        if (instance == 0)
        {
            instance = new Console();
        }
        return instance;
    }

private:
    Console() {}
    ~Console() {}

    SDL_Texture *fontTexture;
    SDL_Rect textureRect;
    SDL_Renderer *renderer;

    //  Virtual Console Dimensions (8x8 characters)
    Point2dInt position;
    Point2dInt virtualConsoleSize;
    Point2dInt characterSize;
    char *consoleBuffer = NULL;

    void LoadFont(const char *fileName);
    void DrawCharacterAt(int x, int y, char c);

public:
    void Init(SDL_Renderer *renderer, int x, int y, int width, int height, const char *fileName, const int fontSize);
    void Cleanup();
    void Render(float time);
    void Clear();

    bool enabled;

    static Console *instance;
};