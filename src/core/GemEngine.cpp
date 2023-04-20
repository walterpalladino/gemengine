#include <iostream>

#include "core/GemEngine.h"
#include "utils/Log.h"
#include "input/InputHandler.h"
#include "core/graphics/text/FontsManager.h"
#include "core/graphics/textures/TextureManager.h"
#include "core/graphics/console/Console.h"

#include "core/graphics/Draw.h"

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
    // SDL_WindowFlags::SDL_WINDOW_RESIZABLE
    //  SDL_WINDOW_OPENGL
    if ((Window = SDL_CreateWindow(
             "Gem Engine",
             SDL_WINDOWPOS_CENTERED,
             SDL_WINDOWPOS_CENTERED,
             windowSize.x, windowSize.y,
             SDL_WINDOW_SHOWN)) == NULL)
    {
        Log::GetInstance()->Error("GemEngine::Init", "Unable to create SDL Window: %s", SDL_GetError());
        return false;
    }

    if ((Renderer = SDL_CreateRenderer(Window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED)) == NULL)
    //| SDL_RENDERER_PRESENTVSYNC
    {
        Log::GetInstance()->Error("GemEngine::Init", "Unable to create renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);

    virtualWindowTexture = SDL_CreateTexture(Renderer, SDL_GetWindowPixelFormat(Window), SDL_TEXTUREACCESS_TARGET, virtualWindowSize.x, virtualWindowSize.y);
    windowTexture = SDL_CreateTexture(Renderer, SDL_GetWindowPixelFormat(Window), SDL_TEXTUREACCESS_TARGET, windowSize.x, windowSize.y);

    InputHandler::Instance()->Init();
    FontsManager::Instance()->Init();
    TextureManager::Instance()->Init(Renderer);

    Log::GetInstance()->Info("GemEngine::Init", "Initialization Completed");

    LoadScenes();

    return true;
}

//------------------------------------------------------------------------------

void GemEngine::PreRender(float time)
{
    SDL_SetRenderDrawColor(Renderer,
                           backgroundColor.x,
                           backgroundColor.y,
                           backgroundColor.z,
                           255);

    if (renderToVirtualWindow)
    {
        SDL_SetRenderTarget(Renderer, virtualWindowTexture);
    }

    SDL_RenderClear(Renderer);
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

        SDL_SetRenderTarget(Renderer, NULL);
        SDL_RenderClear(Renderer);

        SDL_RenderCopyEx(Renderer, virtualWindowTexture, &srcRec, &destRec, 0, NULL, SDL_FLIP_NONE);
    }

    SDL_RenderPresent(Renderer);
}

void GemEngine::Render(float time)
{
    activeScene->Render(time);
}

//------------------------------------------------------------------------------
void GemEngine::Cleanup()
{
    Log::GetInstance()->Info("GemEngine::Cleanup", "Cleanup");

    if (Renderer)
    {
        SDL_DestroyRenderer(Renderer);
        Renderer = NULL;
        Log::GetInstance()->Info("GemEngine::Cleanup", "DestroyRenderer Completed");
    }

    if (Window)
    {
        SDL_DestroyWindow(Window);
        Window = NULL;
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

int GemEngine::Start()
{

    // for (int i = 0; i < argc; ++i)
    //     cout << i << " - " << argv[i] << '\n';

    if (!Init())
        return 0;

    firstRenderTime = SDL_GetTicks();
    lastRenderTime = SDL_GetTicks();

    totalFrames = 0;

    int eventCounter = 0;
    int targetFrameTime = (1000.0f / targetFPS);

    while (Running)
    {
        //  Get Time
        uint32_t frameStart = SDL_GetTicks();

        //   TODO : Check this hardcoded value to calculate it based on target fps
        if (eventCounter % 10 == 0)
        {
            PollEvents();
        }
        eventCounter++;

        float elapsedTimeFromStart = frameStart - firstRenderTime;
        Loop(elapsedTimeFromStart);

        Physics();

        PreRender(elapsedTimeFromStart);
        Render(elapsedTimeFromStart);
        PostRender(elapsedTimeFromStart);

        float frameTime = SDL_GetTicks() - frameStart;

        if (frameTime >= targetFrameTime)
            SDL_Delay(1); // Breath
        else
            SDL_Delay(targetFrameTime - frameTime); // Breath

        totalFrames = totalFrames + 1;

        lastRenderTime = SDL_GetTicks();
    }

    Log::GetInstance()->Info("GemEngine::Execute", "Totl Frames: %.0f FPS : %.2f", totalFrames, GetFPS());

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
    float elapsedTimeFromStart = lastRenderTime - firstRenderTime;
    return totalFrames / elapsedTimeFromStart * 1000.0f;
}

void GemEngine::Physics()
{
}
