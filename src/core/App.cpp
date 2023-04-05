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
        // Log("Unable to Init SDL: %s", SDL_GetError());
        Log::GetInstance()->Error("App::Init", "Unable to Init SDL: %s", SDL_GetError());
        return false;
    }
    // Log("Init SDL Completed");

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        // Log("Unable to Init hinting: %s", SDL_GetError());
        Log::GetInstance()->Error("App::Init", "Unable to Init hinting: %s", SDL_GetError());
    }
    // Log("Init hinting Completed");

    if ((Window = SDL_CreateWindow(
             "My SDL Game",
             SDL_WINDOWPOS_CENTERED,
             SDL_WINDOWPOS_CENTERED,
             WindowWidth, WindowHeight,
             SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)) == NULL)
    {
        // Log("Unable to create SDL Window: %s", SDL_GetError());
        Log::GetInstance()->Error("App::Init", "Unable to create SDL Window: %s", SDL_GetError());
        return false;
    }
    // Log("SDL Window Created");

    // PrimarySurface = SDL_GetWindowSurface(Window);

    if ((Renderer = SDL_CreateRenderer(Window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED)) == NULL)
    //| SDL_RENDERER_PRESENTVSYNC
    {
        // Log("Unable to create renderer");
        // Log("Unable to create renderer: %s", SDL_GetError());
        Log::GetInstance()->Error("App::Init", "Unable to create renderer: %s", SDL_GetError());
        return false;
    }
    // Log("Renderer Created");

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
        //    Log("DestroyRenderer Completed");
        Log::GetInstance()->Info("App::Cleanup", "DestroyRenderer Completed");
    }

    if (Window)
    {
        SDL_DestroyWindow(Window);
        Window = NULL;
        //        Log("DestroyWindow Completed");
        Log::GetInstance()->Info("App::Cleanup", "DestroyWindow Completed");
    }

    SDL_Quit();

    FontsManager::Instance()->Clean();

    //    Log("SDL_Quit Completed");
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

    startTime = std::chrono::steady_clock::now();
    lastTimeOfLoop = std::chrono::steady_clock::now();

    totalFrames = 0;

    int eventCounter = 0;

    while (Running)
    {
        //  Get Time
        std::chrono::steady_clock::time_point timeOfLoop = std::chrono::steady_clock::now();

        float elapsedMilliseconds = std::chrono::duration_cast<chrono::milliseconds>(timeOfLoop - lastTimeOfLoop).count();
        /*
        std::cout << "Elapsed time in milliseconds: " << elapsedMilliseconds << " ms" << std::endl;
        */

        //   TODO : Check this hardcoded value to calculate it based on target fps
        if (eventCounter % 10 == 0)
        {
            PollEvents();
        }
        eventCounter++;

        float elapsedTimeFromStart = std::chrono::duration_cast<chrono::milliseconds>(timeOfLoop - startTime).count();
        Loop(elapsedTimeFromStart);

        Physics();

        Render();

        float elapsedTimeLoop = std::chrono::duration_cast<chrono::milliseconds>(std::chrono::steady_clock::now() - timeOfLoop).count();
        float targetFPS = 90.0f;
        float targetFPSMilliseconds = 1.0f / targetFPS * 1000.0f;

        if (elapsedTimeLoop >= targetFPSMilliseconds)
            SDL_Delay(1); // Breath
        else
            SDL_Delay(targetFPSMilliseconds - elapsedTimeLoop); // Breath

        totalFrames = totalFrames + 1;

        //        cout << (elapsedTimeFromStart / frames) << endl;

        lastTimeOfLoop = timeOfLoop;
    }

    std::chrono::steady_clock::time_point timeNow = std::chrono::steady_clock::now();
    float elapsedTimeFromStart = std::chrono::duration_cast<chrono::milliseconds>(timeNow - startTime).count();
    std::cout << (totalFrames / (elapsedTimeFromStart / 1000.0f)) << std::endl;

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
    /*
        SDL_Event Event;

        while (SDL_PollEvent(&Event) != 0)
        {
            OnEvent(&Event);

            if (Event.type == SDL_QUIT)
                Running = false;
        }
        */
}

void App::Physics()
{
}
