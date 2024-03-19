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
#include "core/sound/SoundManager.h"
#include "core/Config.h"
#include "core/scenes/SceneManager.h"
#include "core/renderer/RenderManager.h"

using namespace std;

//==============================================================================
/**
 * Constructor for the GemEngine class.
 *
 * @param resourceFolder The folder path where the resources are located.
 *
 * @return None
 *
 * @throws None
 */
GemEngine::GemEngine(string resourceFolder)
{
    Log::Instance()->Info("GemEngine::GemEngine", "GemEngine Constructor");
    Log::Instance()->Info("GemEngine::GemEngine", "Resource Folder: %s", resourceFolder.c_str());

    backgroundColor = Point3dInt(0, 0, 0);

    Config::Instance()->config_data.resource_folder = resourceFolder;
    Config::Instance()->Load("config.json");
}

GemEngine::~GemEngine()
{
    Log::Instance()->Info("GemEngine::~GemEngine", "GemEngine Destructor");
}

//------------------------------------------------------------------------------
void GemEngine::OnEvent(SDL_Event *Event)
{
}

//------------------------------------------------------------------------------
bool GemEngine::Init()
{
    Log::Instance()->Info("GemEngine::Init", "Init Framework");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        Log::Instance()->Error("GemEngine::Init", "Unable to Init SDL: %s", SDL_GetError());
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
        Log::Instance()->Error("GemEngine::Init", "Unable to Init hinting: %s", SDL_GetError());
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
        Log::Instance()->Error("GemEngine::Init", "Unable to create SDL Window: %s", SDL_GetError());
        return false;
    }

    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED)) == NULL)
    //| SDL_RENDERER_PRESENTVSYNC
    {
        Log::Instance()->Error("GemEngine::Init", "Unable to create renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

    virtualWindowTexture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_TARGET, virtualWindowSize.x, virtualWindowSize.y);
    windowTexture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_TARGET, windowSize.x, windowSize.y);

    InputHandler::Instance()->Init();
    FontsManager::Instance()->Init();
    TextureManager::Instance()->Init(renderer);
    SoundManager::Instance()->Init();

    Log::Instance()->Info("GemEngine::Init", "Initialization Completed");

    Console::Instance()->Init(renderer);
    Log::Instance()->Info("GemEngine::Init", "Console Configured");

    SceneManager::Instance()->LoadScenes(renderer);
    Log::Instance()->Info("GemEngine::Init", "Scenes Loaded");

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
    Console::Instance()->Render(time);
    SceneManager::Instance()->RenderActiveScene(time);
}

//------------------------------------------------------------------------------
void GemEngine::Cleanup()
{
    Log::Instance()->Info("GemEngine::Cleanup", "Cleanup");

    SceneManager::Instance()->Clean();

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
        Log::Instance()->Info("GemEngine::Cleanup", "DestroyRenderer Completed");
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
        Log::Instance()->Info("GemEngine::Cleanup", "DestroyWindow Completed");
    }

    SDL_DestroyTexture(virtualWindowTexture);
    SDL_DestroyTexture(windowTexture);

    SDL_Quit();

    FontsManager::Instance()->Clean();
    TextureManager::Instance()->Clean();
    SoundManager::Instance()->Clean();

    Console::Instance()->Cleanup();

    Log::Instance()->Info("GemEngine::Cleanup", "SDL_Quit Completed");
}

//------------------------------------------------------------------------------

int GemEngine::Start()
{
    Log::Instance()->Info("GemEngine::Start", "Start()");

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

    if (!Init())
    {
        Log::Instance()->Error("GemEngine::Start", "Initialization Failed");
        return 0;
    }

    firstRenderTick = SDL_GetTicks();
    lastRenderTime = 0;

    totalFrames = 0;

    int eventCounter = 0;
    uint32_t targetFrameTime = (1000 / targetFPS);

    LoopInit();

    Log::Instance()->Info("GemEngine::Start", "Starting Game Loop");

    Scene *newScene = SceneManager::Instance()->activeScene;

    while (Running)
    {

        if ((newScene != NULL) && (SceneManager::Instance()->activeScene != newScene))
        {
            SceneManager::Instance()->activeScene = newScene;
            newScene = NULL;
            // cout << "Switching to scene: " << SceneManager::Instance()->activeScene->name << endl;
        }

        //  Get Time
        startFrameTick = SDL_GetTicks();

        //   TODO : Check this hardcoded value to calculate it based on target fps
        // if (eventCounter % 10 == 0)
        {
            PollEvents();
        }
        eventCounter++;

        float elapsedTimeFromStart = startFrameTick - firstRenderTick;

        // Logic loop
        newScene = Loop(elapsedTimeFromStart);

        SceneManager::Instance()->Physics(elapsedTimeFromStart);

        PreRender(elapsedTimeFromStart);
        Render(elapsedTimeFromStart);

        SceneManager::Instance()->DebugRender(renderer, elapsedTimeFromStart);

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

    Log::Instance()->Info("GemEngine::Execute", "Total Frames: %.0f FPS : %.2f", totalFrames, GetFPS());

    Cleanup();

    Log::Instance()->Info("GemEngine::Execute", "Good Bye!");

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
