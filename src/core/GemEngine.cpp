#include <iostream>

#include "core/GemEngine.h"
#include "utils/Log.h"
#include "input/InputHandler.h"
#include "core/graphics/text/FontsManager.h"
#include "core/graphics/textures/TextureManager.h"

using namespace std;

//==============================================================================
GemEngine::GemEngine()
{
    Log::GetInstance()->Info("GemEngine::GemEngine", "GemEngine Constructor");
    scenes.reserve(MAX_SCENES_PER_APP);
    activeScene = NULL;
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

    if ((Window = SDL_CreateWindow(
             "Gem Engine",
             SDL_WINDOWPOS_CENTERED,
             SDL_WINDOWPOS_CENTERED,
             WindowWidth, WindowHeight,
             SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)) == NULL)
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

    InputHandler::Instance()->Init();
    FontsManager::Instance()->Init();
    TextureManager::Instance()->Init(Renderer);

    Log::GetInstance()->Info("GemEngine::Init", "Initialization Completed");

    LoadScenes();

    return true;
}

//------------------------------------------------------------------------------
void GemEngine::Render(float time)
{
    // SDL_RenderClear(Renderer);
    activeScene->Render(time);
    // SDL_RenderPresent(Renderer);
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

    SDL_Quit();

    FontsManager::Instance()->Clean();
    TextureManager::Instance()->Clean();

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
int GemEngine::Execute(int argc, char *argv[])
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

        Render(elapsedTimeFromStart);

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