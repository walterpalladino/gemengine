#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "core/gemobject/GemObject.h"
#include "math/Point2dInt.h"
#include "math/Point3dInt.h"

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

    Point3dInt color;

    void LoadFont(const char *fileName);
    void DrawCharacterAt(int x, int y, char c);

    void SetCharacterAt(int x, int y, char c);
    void SetCharacterAndUpdateCursor(char c);

    Point2dInt cursorPosition = Point2dInt(0, 0);

    void Init(SDL_Renderer *renderer, int x, int y, int width, int height, const char *fileName, const int fontSize);

public:
    void Init(SDL_Renderer *renderer);
    void Cleanup();
    void Render(float time);
    void Clear();
    void PutCharacterAt(int x, int y, char c);
    void Print(const char *text);
    void SetCursorAt(int x, int y);
    const Point2dInt GetCursorPosition();

    void SetColor(int x, int y, int z);
    const Point3dInt GetColor();

    bool enabled;

    static Console *instance;
};