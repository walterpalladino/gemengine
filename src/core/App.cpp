#include <iostream>

#include "core/App.h"
#include "utils/Log.h"
#include "input/InputHandler.h"
#include "core/text/FontsManager.h"

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

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
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

    Log::GetInstance()->Info("App::Init", "Initialization Completed");

    LoadScenes();

    return true;
}

//------------------------------------------------------------------------------
void App::Render()
{
    // SDL_RenderClear(Renderer);
    activeScene->Render();
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

    // startTime = std::chrono::steady_clock::now();
    // lastTimeOfLoop = std::chrono::steady_clock::now();
    firstRenderTime = SDL_GetTicks();
    lastRenderTime = SDL_GetTicks();

    totalFrames = 0;

    int eventCounter = 0;
    int targetFrameTime = (1000.0f / targetFPS);

    while (Running)
    {
        //  Get Time
        // std::chrono::steady_clock::time_point timeOfLoop = std::chrono::steady_clock::now();
        uint32_t frameStart = SDL_GetTicks();

        //        float elapsedMilliseconds = std::chrono::duration_cast<chrono::milliseconds>(timeOfLoop - lastTimeOfLoop).count();
        // float elapsedMilliseconds = timeOfLoopTicks - lastTimeOfLoopTicks;
        /*
        std::cout << "Elapsed time in milliseconds: " << elapsedMilliseconds << " ms" << std::endl;
        */

        //   TODO : Check this hardcoded value to calculate it based on target fps
        if (eventCounter % 10 == 0)
        {
            PollEvents();
        }
        eventCounter++;

        // float elapsedTimeFromStart = std::chrono::duration_cast<chrono::milliseconds>(timeOfLoop - startTime).count();
        float elapsedTimeFromStart = frameStart - firstRenderTime;
        Loop(elapsedTimeFromStart);

        Physics();

        Render();

        // float elapsedTimeLoop = std::chrono::duration_cast<chrono::milliseconds>(std::chrono::steady_clock::now() - timeOfLoop).count();
        float frameTime = SDL_GetTicks() - frameStart;

        if (frameTime >= targetFrameTime)
            SDL_Delay(1); // Breath
        else
            SDL_Delay(targetFrameTime - frameTime); // Breath

        totalFrames = totalFrames + 1;

        //        cout << (elapsedTimeFromStart / frames) << endl;

        // lastTimeOfLoop = timeOfLoop;
        lastRenderTime = SDL_GetTicks();
    }
    /*
        // std::chrono::steady_clock::time_point timeNow = std::chrono::steady_clock::now();
        uint32_t timeNow = SDL_GetTicks();
        // float elapsedTimeFromStart = std::chrono::duration_cast<chrono::milliseconds>(timeNow - startTime).count();
        float elapsedTimeFromStart = timeNow - startTimeTicks;
        std::cout << (totalFrames / (elapsedTimeFromStart / 1000.0f)) << std::endl;
    */
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
    // float elapsedTimeFromStart = std::chrono::duration_cast<chrono::milliseconds>(lastTimeOfLoop - startTime).count();
    float elapsedTimeFromStart = lastRenderTime - firstRenderTime;
    return totalFrames / elapsedTimeFromStart * 1000.0f;
}

void App::Physics()
{
}
