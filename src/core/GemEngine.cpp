#include <iostream>

#include "core/GemEngine.h"
#include "utils/Log.h"
#include "utils/StringUtils.h"
#include "core/input/InputHandler.h"
#include "core/graphics/text/FontsManager.h"
#include "core/graphics/textures/TextureManager.h"
#include "core/graphics/console/Console.h"
#include "core/sound/SoundManager.h"
#include "core/config/Config.h"
#include "core/scenes/SceneManager.h"
#include "core/renderer/RenderManager.h"
#include "core/Context.h"
#include "core/exceptions/CoreInitializationException.h"
#include "core/physics/PhysicsEngine.h"

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

    Config::Instance()->config_data.resource_folder = resourceFolder;
    Config::Instance()->Load("config.json");
}

GemEngine::~GemEngine()
{
    Log::Instance()->Info("GemEngine::~GemEngine", "GemEngine Destructor");
}

void GemEngine::Render(float time)
{
    Console::Instance()->Render(time);
    SceneManager::Instance()->RenderActiveScene(time);
}

void GemEngine::Init()
{
    Log::Instance()->Info("GemEngine::Init", "Init()");

    Context::Instance()->targetFPS = Config::Instance()->config_data.target_fps;

    renderer = RenderManager::Instance()->Init();
    if (renderer == NULL)
    {
        Log::Instance()->Error("GemEngine::Start", "RenderManager failed to initialize");
        throw CoreInitializationException("RenderManager failed to initialize");
    }

    InputHandler::Instance()->Init();
    FontsManager::Instance()->Init();
    TextureManager::Instance()->Init(renderer);
    SoundManager::Instance()->Init();

    Log::Instance()->Info("GemEngine::Init", "Initialization Completed");

    Console::Instance()->Init(renderer);
    Log::Instance()->Info("GemEngine::Init", "Console Configured");

    EventManager::Instance()->Init();

    SceneManager::Instance()->LoadScenes(renderer);

    //  Init FPS Comter
    Context::Instance()->InitFPSCounter();

    // Timer
    processTimer = SDL_AddTimer(10000, ProcessTimerCallback, this);

    if (!SceneManager::Instance()->ValidateScenesLogic())
    {
        Log::Instance()->Error("GemEngine::Start", "ValidateScenesLogic Failed");
        throw CoreInitializationException("ValidateScenesLogic Failed");
    }
}

//------------------------------------------------------------------------------
void GemEngine::Cleanup()
{
    Log::Instance()->Info("GemEngine::Cleanup", "Cleanup");

    SceneManager::Instance()->Clean();

    RenderManager::Instance()->Cleanup();

    FontsManager::Instance()->Clean();
    TextureManager::Instance()->Clean();
    SoundManager::Instance()->Clean();

    Console::Instance()->Cleanup();

    EventManager::Instance()->Cleanup();

    //  Timer
    SDL_RemoveTimer(processTimer);

    Log::Instance()->Info("GemEngine::Cleanup", "SDL_Quit Completed");
}

//------------------------------------------------------------------------------

int GemEngine::Start()
{
    Log::Instance()->Info("GemEngine::Start", "Start()");

    Init();

    Log::Instance()->Info("GemEngine::Start", "Starting Game Loop");

    while (engineStatus.isRunning)
    {

        engineStatus = EventManager::Instance()->HandleEvents();

        float elapsedTimeFromStart = Context::Instance()->StartFPSFrameCounter();

        SceneManager::Instance()->Loop(elapsedTimeFromStart, engineStatus.isPaused);

        PhysicsEngine::Physics(elapsedTimeFromStart);
        RenderManager::Instance()->PreRender(elapsedTimeFromStart);
        Render(elapsedTimeFromStart);
        PhysicsEngine::DebugRender(renderer, elapsedTimeFromStart);
        RenderManager::Instance()->PostRender(elapsedTimeFromStart);

        Context::Instance()->WaitForEndFrame();
    }

    Log::Instance()->Info("GemEngine::Execute", "Total Frames: %.0f FPS : %.2f", Context::Instance()->totalFrames, Context::Instance()->GetFPS());

    Cleanup();

    Log::Instance()->Info("GemEngine::Execute", "Good Bye!");

    return 1;
}

Uint32 GemEngine::ProcessTimerCallback(Uint32 interval, void *param)
{
    return ((GemEngine *)param)->ProcessTimer(interval);
}

Uint32 GemEngine::ProcessTimer(Uint32 interval)
{
    cout << "ProcessTimer : " << interval << endl;

    return (interval);
}
