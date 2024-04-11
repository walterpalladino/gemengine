#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>

#include "math/Point2dInt.h"
#include "math/Point3dInt.h"
#include "math/RectInt.h"

using namespace std;

class RenderManager
{

public:
    static RenderManager *Instance()
    {
        if (instance == 0)
        {
            instance = new RenderManager();
        }
        return instance;
    }

private:
    RenderManager() {}
    ~RenderManager() {}

    static RenderManager *instance;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Texture *virtualWindowTexture = NULL;
    SDL_Texture *windowTexture = NULL;

    Point2dInt windowSize = Point2dInt(1280, 720);
    RectInt boundaries;

    // Virtual Screen Dimensions (pixels)
    Point2dInt virtualWindowSize = Point2dInt(384, 216);

    int scaleQuality = 0;
    bool renderToVirtualWindow = true;

public:
    Point3dInt backgroundColor;

public:
    SDL_Renderer *Init();
    void Cleanup();
    void PreRender(float time);
    void PostRender(float time);
    Point2dInt GetWindowSize() { return windowSize; }
    RectInt GetBoundaries() { return boundaries; }
};