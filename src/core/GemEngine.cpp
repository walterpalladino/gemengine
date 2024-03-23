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
#include "core/Context.h"
#include "core/scenes/SceneLogic.h"
#include "core/scenes/SceneTransition.h"

#include "core/events/EventManager.h"

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

    Context::Instance()->targetFPS = Config::Instance()->config_data.target_fps;

    renderer = RenderManager::Instance()->Init();
    if (renderer == NULL)
    {
        Log::Instance()->Error("GemEngine::Start", "Initialization Failed");
        return 0;
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

    LoopInit();

    // Timer
    processTimer = SDL_AddTimer(10000, ProcessTimerCallback, this);

    Log::Instance()->Info("GemEngine::Start", "Starting Game Loop");

    //  Set the default scene. Always needs to start with a scene
    Scene *newScene = SceneManager::Instance()->activeScene;
    SceneLogic *activeSceneLogic = SceneManager::Instance()->GetActiveSceneLogic();
    if (SceneManager::Instance()->activeScene != NULL)
    {
        activeSceneLogic->Init(SceneManager::Instance()->activeScene);
    }

    SceneTransition newSceneTransition;

    while (isRunning)
    {
        // Check if scene changed
        if ((newScene != NULL) && (SceneManager::Instance()->activeScene != newScene))
        {
            // If switching to a new scene so first clean the actual one
            if (SceneManager::Instance()->activeScene != NULL)
            {
                activeSceneLogic->Clean();
            }

            // Set the new scene
            SceneManager::Instance()->activeScene = newScene;
            newScene = NULL;
            // cout << "Switching to scene: " << SceneManager::Instance()->activeScene->name << endl;
            activeSceneLogic = SceneManager::Instance()->GetActiveSceneLogic();

            //  If it is a new scene then init the logic
            if (SceneManager::Instance()->activeScene != NULL)
            {
                activeSceneLogic->Init(SceneManager::Instance()->activeScene);
            }
        }

        PollEvents();

        float elapsedTimeFromStart = Context::Instance()->StartFPSFrameCounter();

        // Logic loop
        if (activeSceneLogic != NULL)
        {
            // When paused do not update logic
            // if (!newSceneTransition.isPaused)
            if (!isPaused)
            {
                newSceneTransition = activeSceneLogic->Loop(elapsedTimeFromStart);
                SceneManager::Instance()->UpdateActiveScene(elapsedTimeFromStart);
            }
            newScene = newSceneTransition.scene;
        }

        SceneManager::Instance()->Physics(elapsedTimeFromStart);
        RenderManager::Instance()->PreRender(elapsedTimeFromStart);
        Render(elapsedTimeFromStart);
        SceneManager::Instance()->DebugRender(renderer, elapsedTimeFromStart);
        RenderManager::Instance()->PostRender(elapsedTimeFromStart);

        Context::Instance()->WaitForEndFrame();
    }

    Log::Instance()->Info("GemEngine::Execute", "Total Frames: %.0f FPS : %.2f", Context::Instance()->totalFrames, Context::Instance()->GetFPS());

    Cleanup();

    Log::Instance()->Info("GemEngine::Execute", "Good Bye!");

    return 1;
}

void GemEngine::PollEvents()
{

    //  Get first the Custom Events
    SDL_Event event;
    int eventCounter = SDL_PeepEvents(&event, 1,
                                      SDL_GETEVENT,
                                      EventManager::Instance()->GEMENGINE_EVENT_TYPE,
                                      EventManager::Instance()->GEMENGINE_EVENT_TYPE);
    if (eventCounter > 0)
    {
        cout << "GemEngine::PollEvents : Get Custom Event Type : " << event.type << " user code : " << EventManager::GEMEventCodeToString(event.user.code) << endl;

        if (event.user.code == EventManager::GEMEVENT_CODE_PAUSE)
        {
            isPaused = true;
        }
        else if (event.user.code == EventManager::GEMEVENT_CODE_RESUME)
        {
            isPaused = false;
        }
    }

    //  Get the Standard Events
    bool quit = InputHandler::Instance()->Update();
    if (quit)
    {
        isRunning = false;
    }
    /*
    else
    {
        if (InputHandler::Instance()->WasKeyPressed(SDL_SCANCODE_P))
        {
            // cout << "Pause Scene" << endl;
            isPaused = !isPaused;
        }
    }
    */
    else
    {
        //  Resume Scene
        if (InputHandler::Instance()->WasKeyPressed(SDL_SCANCODE_R))
        {
            isPaused = false;
        }
    }
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
