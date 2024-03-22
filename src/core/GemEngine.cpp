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

//------------------------------------------------------------------------------
void GemEngine::OnEvent(SDL_Event *Event)
{
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

    SceneManager::Instance()->LoadScenes(renderer);

    //  Init FPS Comter
    Context::Instance()->InitFPSCounter();

    // int eventCounter = 0;

    LoopInit();

    Log::Instance()->Info("GemEngine::Start", "Starting Game Loop");

    Scene *newScene = SceneManager::Instance()->activeScene;
    SceneLogic *activeSceneLogic = SceneManager::Instance()->GetActiveSceneLogic();
    if (SceneManager::Instance()->activeScene != NULL)
    {
        activeSceneLogic->Init(SceneManager::Instance()->activeScene);
    }

    SceneTransition newSceneTransition;

    while (Running)
    {
        // Check if scene changed
        if ((newScene != NULL) && (SceneManager::Instance()->activeScene != newScene))
        {
            if (SceneManager::Instance()->activeScene != NULL)
            {
                activeSceneLogic->Clean();
            }
            SceneManager::Instance()->activeScene = newScene;
            newScene = NULL;
            // cout << "Switching to scene: " << SceneManager::Instance()->activeScene->name << endl;
            activeSceneLogic = SceneManager::Instance()->GetActiveSceneLogic();
            if (SceneManager::Instance()->activeScene != NULL)
            {
                activeSceneLogic->Init(SceneManager::Instance()->activeScene);
            }
        }

        // if (eventCounter % 10 == 0)
        {
            PollEvents();
        }
        // eventCounter++;

        float elapsedTimeFromStart = Context::Instance()->StartFPSFrameCounter();

        // Logic loop
        if (activeSceneLogic != NULL)
        {
            newSceneTransition = activeSceneLogic->Loop(elapsedTimeFromStart);
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

    bool quit = InputHandler::Instance()->Update();
    if (quit)
    {
        Running = false;
    }
}
