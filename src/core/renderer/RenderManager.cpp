
#include "core/renderer/RenderManager.h"

#include "utils/Log.h"
#include "utils/StringUtils.h"
#include "core/config/Config.h"

RenderManager *RenderManager::instance = 0;

SDL_Renderer *RenderManager::Init()
{
    Log::Instance()->Info("RenderManager::Init", "Init Framework");

    backgroundColor = Point3dInt(0, 0, 0);

    //  Cache some configuration values
    windowSize = Point2dInt(Config::Instance()->config_data.window_width, Config::Instance()->config_data.window_height);

    // Virtual Screen Dimensions (pixels)
    virtualWindowSize = Point2dInt(Config::Instance()->config_data.virtual_window_width, Config::Instance()->config_data.virtual_window_height);
    renderToVirtualWindow = Config::Instance()->config_data.use_virtual_window;
    scaleQuality = Config::Instance()->config_data.aa_level;

    if (renderToVirtualWindow)
    {
        boundaries = RectInt(0, 0, virtualWindowSize.x - 1, virtualWindowSize.y - 1);
    }
    else
    {
        boundaries = RectInt(0, 0, windowSize.x - 1, windowSize.y - 1);
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
    {
        Log::Instance()->Error("RenderManager::Init", "Unable to Init SDL: %s", SDL_GetError());
        return NULL;
    }

    //  TODO : Change to parameter to select when use or not antialiasing
    //  SDL_HINT_RENDER_SCALE_QUALITY
    //  0 or nearest / nearest pixel sampling
    //  1 or linear / linear filtering (supported by OpenGL and Direct3D)
    //  2 or best / anisotropic filtering (supported by Direct3D)
    char *scaleQualityValue = new char[2];
    sprintf(scaleQualityValue, "%i", scaleQuality);
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scaleQualityValue))
    {
        Log::Instance()->Error("RenderManager::Init", "Unable to Init hinting: %s", SDL_GetError());
    }
    delete[] scaleQualityValue;
    scaleQualityValue = NULL;

    // SDL_WindowFlags::SDL_WINDOW_RESIZABLE
    //  SDL_WINDOW_OPENGL
    if ((window = SDL_CreateWindow(
             "Gem Engine",
             SDL_WINDOWPOS_CENTERED,
             SDL_WINDOWPOS_CENTERED,
             windowSize.x, windowSize.y,
             SDL_WINDOW_SHOWN)) == NULL)
    {
        Log::Instance()->Error("RenderManager::Init", "Unable to create SDL Window: %s", SDL_GetError());
        return NULL;
    }

    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED)) == NULL)
    //| SDL_RENDERER_PRESENTVSYNC
    {
        Log::Instance()->Error("RenderManager::Init", "Unable to create renderer: %s", SDL_GetError());
        return NULL;
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

    virtualWindowTexture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_TARGET, virtualWindowSize.x, virtualWindowSize.y);
    windowTexture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_TARGET, windowSize.x, windowSize.y);

    Log::Instance()->Info("RenderManager::Init", "Initialization Completed");

    return renderer;
}

void RenderManager::Cleanup()
{
    Log::Instance()->Info("RenderManager::Cleanup", "Cleanup");

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
        Log::Instance()->Info("RenderManager::Cleanup", "DestroyRenderer Completed");
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
        Log::Instance()->Info("RenderManager::Cleanup", "DestroyWindow Completed");
    }

    SDL_DestroyTexture(virtualWindowTexture);
    SDL_DestroyTexture(windowTexture);

    SDL_Quit();

    Log::Instance()->Info("RenderManager::Cleanup", "SDL_Quit Completed");
}

void RenderManager::PreRender(float time)
{
    SDL_SetRenderDrawColor(renderer,
                           backgroundColor.x,
                           backgroundColor.y,
                           backgroundColor.z,
                           255);

    if (renderToVirtualWindow)
    {
        SDL_SetRenderTarget(renderer, virtualWindowTexture);
    }

    SDL_RenderClear(renderer);
}

void RenderManager::PostRender(float time)
{
    if (renderToVirtualWindow)
    {
        int width = virtualWindowSize.x;
        int height = virtualWindowSize.y;

        float targetRatio = (float)virtualWindowSize.x / (float)virtualWindowSize.y;
        float windowRatio = (float)windowSize.x / (float)windowSize.y;

        if (targetRatio > windowRatio)
        {
            width = windowSize.x;
            height = width / targetRatio;
        }
        else
        {
            height = windowSize.y;
            width = height * targetRatio;
        }
        // printf("%f x %f\n", targetRatio, windowRatio);
        // printf("%i x %i\n", width, height);

        SDL_Rect srcRec = SDL_Rect();
        srcRec.x = 0;
        srcRec.y = 0;
        srcRec.w = width;
        srcRec.h = height;

        SDL_Rect destRec = SDL_Rect();
        destRec.x = (windowSize.x - width) / 2;
        destRec.y = (windowSize.y - height) / 2;
        destRec.w = width;
        destRec.h = height;

        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderClear(renderer);

        SDL_RenderCopyEx(renderer, virtualWindowTexture, &srcRec, &destRec, 0, NULL, SDL_FLIP_NONE);
    }

    SDL_RenderPresent(renderer);
}