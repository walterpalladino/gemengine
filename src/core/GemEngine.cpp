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
    Log::GetInstance()->Info("GemEngine::GemEngine", "GemEngine Constructor");
    Log::GetInstance()->Info("GemEngine::GemEngine", "Resource Folder: %s", resourceFolder.c_str());

    // scenes.reserve(MAX_SCENES_PER_APP);
    activeScene = NULL;
    backgroundColor = Point3dInt(0, 0, 0);

    Config::Instance()->config_data.resource_folder = resourceFolder;
    Config::Instance()->Load("config.json");
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

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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
    SoundManager::Instance()->Init();

    Log::GetInstance()->Info("GemEngine::Init", "Initialization Completed");

    Console::Instance()->Init(renderer);
    Log::GetInstance()->Info("GemEngine::Init", "Console Configured");

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
    Console::Instance()->Render(time);
    activeScene->Render(time);
}

//------------------------------------------------------------------------------
void GemEngine::Cleanup()
{
    Log::GetInstance()->Info("GemEngine::Cleanup", "Cleanup");

    //  Clean up scenes
    for (auto scene : scenes)
    {
        Log::GetInstance()->Info("GemEngine::~App", "Deleting scene: %s", scene->name.c_str());
        scene->Cleanup();
        delete scene;
    }
    scenes.clear();

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
    SoundManager::Instance()->Clean();

    Console::Instance()->Cleanup();

    Log::GetInstance()->Info("GemEngine::Cleanup", "SDL_Quit Completed");
}

//------------------------------------------------------------------------------

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

        // Logic loop
        Loop(elapsedTimeFromStart);

        Physics(elapsedTimeFromStart);

        PreRender(elapsedTimeFromStart);
        Render(elapsedTimeFromStart);

        DebugRender(elapsedTimeFromStart);

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

void GemEngine::Physics(float time)
{

    Scene activeScene = *this->activeScene;
    unordered_map<string, GemObject *> objects = activeScene.GetObjects();

    vector<GemObject *> objects_vector = GetColliderEnabledObjects(objects);

    for (int i = 0; i < objects_vector.size() - 1; i++)
    {
        // cout << "Checking collisions for gemobject: " << objects_vector[i]->name << endl;
        objects_vector[i]->collisions.clear();

        for (int j = i + 1; j < objects_vector.size(); j++)
        {
            SDL_Rect AABBi = objects_vector[i]->GetColliderRect();
            SDL_Rect AABBj = objects_vector[j]->GetColliderRect();
            SDL_Rect *AABBcollision = new SDL_Rect();

            // cout << AABBi.x << " " << AABBi.y << " " << AABBi.w << " " << AABBi.h << endl;
            // cout << AABBj.x << " " << AABBj.y << " " << AABBj.w << " " << AABBj.h << endl;

            bool status = SDL_IntersectRect(&AABBi, &AABBj, AABBcollision);
            if (status)
            {
                // cout << "   with gemobject: " << objects_vector[j]->name << endl;
                // cout << "   collision area: " << AABBcollision->x << " " << AABBcollision->y << " " << AABBcollision->w << " " << AABBcollision->h << endl;

                objects_vector[i]->collisions[objects_vector[j]->name] = *AABBcollision;
                objects_vector[j]->collisions[objects_vector[i]->name] = *AABBcollision;
            } /*
             else
             {
                 cout << "   NOT COLLIDED!!! " << endl;
             }*/
        }
    }
}

vector<GemObject *> GemEngine::GetColliderEnabledObjects(unordered_map<string, GemObject *> objects)
{

    vector<GemObject *> objects_vector;

    for (auto &[name, object] : objects)
    {
        if (object->enabled && object->colliderEnabled)
        {
            objects_vector.push_back(object);
        }
    }

    return objects_vector;
}

void GemEngine::LoadScenes()
{
    Log::GetInstance()->Info("GemEngine::LoadScenes", "Load Scenes");

    string resourceFolder = Config::Instance()->config_data.resource_folder;

    for (auto &&scene_name : Config::Instance()->config_data.scenes)
    {
        Log::GetInstance()->Info("GemEngine::LoadScenes", "Loading Scene: %s", scene_name.c_str());

        //  Create & Load Scene
        Scene *newScene = new Scene();
        newScene->Load(StringPrintf("%s/%s", resourceFolder.c_str(), scene_name.c_str()).c_str(), renderer);
        newScene->name = scene_name;

        //  Add Scene to Scenes list
        scenes.push_back(newScene);
    }

    activeScene = scenes.front();

    Log::GetInstance()->Info("GemEngine::LoadScenes", "Load Scenes Completed");
}

void GemEngine::DebugRender(float time)
{
    // cout << "Render debug" << endl;
    Scene activeScene = *this->activeScene;
    unordered_map<string, GemObject *> objects = activeScene.GetObjects();

    //  Render scene objects
    for (auto &[name, object] : objects)
    {
        if (object->enabled && object->colliderEnabled)
        {
            // cout << "Checking : " << object->collisions.size() << " collisions for gemobject: " << object->name << endl;
            if (object->collisions.size() > 0)
            {
                // cout << "Drawing collisions for gemobject: " << object->name << endl;
                //   Render collisions
                for (auto &[name, collision] : object->collisions)
                {
                    object->RenderCollisionRect(renderer, name, {255, 0, 0, 255});
                }
            }
        }
    }
}