#include <iostream>

#include "core/GemEngine.h"
#include "utils/Log.h"
#include "utils/StringUtils.h"
#include "core/input/InputHandler.h"
#include "core/graphics/text/FontsManager.h"
#include "core/graphics/textures/TextureManager.h"
#include "core/graphics/console/Console.h"
#include "core/graphics/WindowManager.h"
#include "core/graphics/draw2d/Draw.h"
#include "core/graphics/draw2d/Rect.h"
#include "core/Config.h"

using namespace std;

//==============================================================================
GemEngine::GemEngine()
{
    Log::GetInstance()->Info("GemEngine::GemEngine", "GemEngine Constructor");
    scenes.reserve(MAX_SCENES_PER_APP);
    activeScene = NULL;
    backgroundColor = Point3dInt(0, 0, 0);
}

GemEngine::~GemEngine()
{
    Log::GetInstance()->Info("GemEngine::~GemEngine", "GemEngine Destructor");
}

//------------------------------------------------------------------------------
void GemEngine::OnEvent(SDL_Event *Event)
{
}

void GemEngine::SetResourceFolder(string resourceFolder)
{
    this->resourceFolder = resourceFolder;

    // Load config
    string configFileName = StringPrintf("%s/%s", GetResourceFolder().c_str(), "config.json");
    Config::Instance()->Load(configFileName);
}

string GemEngine::GetResourceFolder()
{
    return resourceFolder;
}

//------------------------------------------------------------------------------
bool GemEngine::Init()
{
    Log::GetInstance()->Info("GemEngine::Init", "Init Framework");

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Log::GetInstance()->Error("GemEngine::Init", "Unable to Init SDL: %s", SDL_GetError());
        return false;
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
        Log::GetInstance()->Error("GemEngine::Init", "Unable to Init hinting: %s", SDL_GetError());
    }
    delete scaleQualityValue;

    // SDL_WindowFlags::SDL_WINDOW_RESIZABLE
    //  SDL_WINDOW_OPENGL
    if ((window = SDL_CreateWindow(
             "Gem Engine",
             SDL_WINDOWPOS_CENTERED,
             SDL_WINDOWPOS_CENTERED,
             windowSize.x, windowSize.y,
             SDL_WINDOW_SHOWN)) == NULL)
    {
        Log::GetInstance()->Error("GemEngine::Init", "Unable to create SDL Window: %s", SDL_GetError());
        return false;
    }

    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED)) == NULL)
    //| SDL_RENDERER_PRESENTVSYNC
    {
        Log::GetInstance()->Error("GemEngine::Init", "Unable to create renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

    virtualWindowTexture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_TARGET, virtualWindowSize.x, virtualWindowSize.y);
    windowTexture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_TARGET, windowSize.x, windowSize.y);

    InputHandler::Instance()->Init();
    FontsManager::Instance()->Init();
    TextureManager::Instance()->Init(renderer);

    Log::GetInstance()->Info("GemEngine::Init", "Initialization Completed");

    LoadScenes();
    Log::GetInstance()->Info("GemEngine::Init", "Scenes Loaded");

    return true;
}

//------------------------------------------------------------------------------

void GemEngine::PreRender(float time)
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

void GemEngine::PostRender(float time)
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

void GemEngine::Render(float time)
{
    activeScene->Render(time);
}

//------------------------------------------------------------------------------
void GemEngine::Cleanup()
{
    Log::GetInstance()->Info("GemEngine::Cleanup", "Cleanup");

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
        Log::GetInstance()->Info("GemEngine::Cleanup", "DestroyRenderer Completed");
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
        Log::GetInstance()->Info("GemEngine::Cleanup", "DestroyWindow Completed");
    }

    SDL_DestroyTexture(virtualWindowTexture);
    SDL_DestroyTexture(windowTexture);

    SDL_Quit();

    FontsManager::Instance()->Clean();
    TextureManager::Instance()->Clean();

    Console::Instance()->Cleanup();

    Log::GetInstance()->Info("GemEngine::Cleanup", "SDL_Quit Completed");

    //  Clean up scenes
    for (auto scene : scenes)
    {
        Log::GetInstance()->Info("GemEngine::~App", "Deleting scene: %s", scene->name.c_str());
        scene->Cleanup();
        delete scene;
    }
    scenes.clear();
}

//------------------------------------------------------------------------------
/*
int GemEngine::Start(int windowWidth, int windowHeight, int virtualWindowWidth, int virtualWindowHeight)
{
    windowSize = Point2dInt(windowWidth, windowHeight);

    // Virtual Screen Dimensions (pixels)
    virtualWindowSize = Point2dInt(virtualWindowWidth, virtualWindowHeight);
    renderToVirtualWindow = true;

    return Start();
}

int GemEngine::Start(int windowWidth, int windowHeight)
{
    windowSize = Point2dInt(windowWidth, windowHeight);

    renderToVirtualWindow = false;

    return Start();
}
*/
int GemEngine::Start()
{
    Log::GetInstance()->Info("GemEngine::Start", "Start()");

    windowSize = Point2dInt(Config::Instance()->config_data.window_width, Config::Instance()->config_data.window_height);

    // Virtual Screen Dimensions (pixels)
    virtualWindowSize = Point2dInt(Config::Instance()->config_data.virtual_window_width, Config::Instance()->config_data.virtual_window_height);
    renderToVirtualWindow = Config::Instance()->config_data.use_virtual_window;
    scaleQuality = Config::Instance()->config_data.aa_level;
    targetFPS = Config::Instance()->config_data.target_fps;

    if (renderToVirtualWindow)
    {
        WindowManager::Instance()->boundaries = RectInt(0, 0, virtualWindowSize.x - 1, virtualWindowSize.y - 1);
    }
    else
    {
        WindowManager::Instance()->boundaries = RectInt(0, 0, windowSize.x - 1, windowSize.y - 1);
    }

    // for (int i = 0; i < argc; ++i)
    //     cout << i << " - " << argv[i] << '\n';

    if (!Init())
    {
        Log::GetInstance()->Error("GemEngine::Start", "Initialization Failed");
        return 0;
    }

    firstRenderTick = SDL_GetTicks();
    lastRenderTime = 0;

    totalFrames = 0;

    int eventCounter = 0;
    uint32_t targetFrameTime = (1000 / targetFPS);

    while (Running)
    {
        //  Get Time
        startFrameTick = SDL_GetTicks();

        //   TODO : Check this hardcoded value to calculate it based on target fps
        // if (eventCounter % 10 == 0)
        {
            PollEvents();
        }
        eventCounter++;

        float elapsedTimeFromStart = startFrameTick - firstRenderTick;
        Loop(elapsedTimeFromStart);

        Physics();

        PreRender(elapsedTimeFromStart);
        Render(elapsedTimeFromStart);
        PostRender(elapsedTimeFromStart);

        lastRenderTime = SDL_GetTicks() - startFrameTick;

        if (lastRenderTime >= targetFrameTime)
            SDL_Delay(1); // Breath
        else
            SDL_Delay(targetFrameTime - lastRenderTime); // Breath

        totalFrames = totalFrames + 1;

        endFrameTick = SDL_GetTicks();

        lastFrameTime = endFrameTick - startFrameTick;
    }

    Log::GetInstance()->Info("GemEngine::Execute", "Total Frames: %.0f FPS : %.2f", totalFrames, GetFPS());

    Cleanup();

    Log::GetInstance()->Info("GemEngine::Execute", "Good Bye!");

    return 1;
}

void GemEngine::PollEvents()
{

    bool quit = InputHandler::Instance()->Update();
    if (quit)
    {
        Running = false;
    }
}

float GemEngine::GetFPS()
{
    float elapsedTimeFromStart = endFrameTick - firstRenderTick;
    return elapsedTimeFromStart > 0 ? (float)totalFrames / elapsedTimeFromStart * 1000.0f : 0.0;
}
/*
uint32_t GemEngine::GetLastFrameTime()
{
    return lastFrameTime;
}
*/
void GemEngine::Physics()
{
}
