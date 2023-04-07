#include <iostream>

#include "core/App.h"
#include "utils/Log.h"
#include "input/InputHandler.h"
#include "core/graphics/text/FontsManager.h"
#include "core/graphics/textures/TextureManager.h"

using namespace std;

//==============================================================================
App::App()
{
    Log::GetInstance()->Info("App::App", "App Constructor");
    scenes.reserve(MAX_SCENES_PER_APP);
    activeScene = NULL;
}

App::~App()
{
    Log::GetInstance()->Info("App::~App", "App Destructor");
}

//------------------------------------------------------------------------------
void App::OnEvent(SDL_Event *Event)
{
}

//------------------------------------------------------------------------------
bool App::Init()
{
    Log::GetInstance()->Info("App::Init", "Init Framework");

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Log::GetInstance()->Error("App::Init", "Unable to Init SDL: %s", SDL_GetError());
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
        Log::GetInstance()->Error("App::Init", "Unable to Init hinting: %s", SDL_GetError());
    }

    if ((Window = SDL_CreateWindow(
             "Gem Engine",
             SDL_WINDOWPOS_CENTERED,
             SDL_WINDOWPOS_CENTERED,
             WindowWidth, WindowHeight,
             SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)) == NULL)
    {
        Log::GetInstance()->Error("App::Init", "Unable to create SDL Window: %s", SDL_GetError());
        return false;
    }

    if ((Renderer = SDL_CreateRenderer(Window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED)) == NULL)
    //| SDL_RENDERER_PRESENTVSYNC
    {
        Log::GetInstance()->Error("App::Init", "Unable to create renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);

    InputHandler::Instance()->Init();
    FontsManager::Instance()->Init();
    TextureManager::Instance()->Init(Renderer);

    Log::GetInstance()->Info("App::Init", "Initialization Completed");

    LoadScenes();

    return true;
}

//------------------------------------------------------------------------------
void App::Render(float time)
{
    // SDL_RenderClear(Renderer);
    activeScene->Render(time);
    // SDL_RenderPresent(Renderer);
}

//------------------------------------------------------------------------------
void App::Cleanup()
{
    Log::GetInstance()->Info("App::Cleanup", "Cleanup");

    if (Renderer)
    {
        SDL_DestroyRenderer(Renderer);
        Renderer = NULL;
        Log::GetInstance()->Info("App::Cleanup", "DestroyRenderer Completed");
    }

    if (Window)
    {
        SDL_DestroyWindow(Window);
        Window = NULL;
        Log::GetInstance()->Info("App::Cleanup", "DestroyWindow Completed");
    }

    SDL_Quit();

    FontsManager::Instance()->Clean();
    TextureManager::Instance()->Clean();

    Log::GetInstance()->Info("App::Cleanup", "SDL_Quit Completed");

    //  Clean up scenes
    for (auto scene : scenes)
    {
        Log::GetInstance()->Info("App::~App", "Deleting scene: %s", scene->name.c_str());
        scene->Cleanup();
        delete scene;
    }
    scenes.clear();
}

//------------------------------------------------------------------------------
int App::Execute(int argc, char *argv[])
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

    Log::GetInstance()->Info("App::Execute", "Totl Frames: %.0f FPS : %.2f", totalFrames, GetFPS());

    Cleanup();

    Log::GetInstance()->Info("App::Execute", "Good Bye!");

    return 1;
}

void App::PollEvents()
{

    bool quit = InputHandler::Instance()->Update();
    if (quit)
    {
        Running = false;
    }
}

float App::GetFPS()
{
    float elapsedTimeFromStart = lastRenderTime - firstRenderTime;
    return totalFrames / elapsedTimeFromStart * 1000.0f;
}

void App::Physics()
{
}
