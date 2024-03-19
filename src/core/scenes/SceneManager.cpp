
#include "core/scenes/SceneManager.h"
#include "core/scenes/Scene.h"
#include "utils/Log.h"
#include "utils/StringUtils.h"
#include "core/Config.h"

SceneManager *SceneManager::instance = 0;

void SceneManager::LoadScenes(SDL_Renderer *renderer)
{
    Log::Instance()->Info("GemEngine::LoadScenes", "Load Scenes");

    string resourceFolder = Config::Instance()->config_data.resource_folder;

    for (auto &&scene_name : Config::Instance()->config_data.scenes)
    {
        Log::Instance()->Info("GemEngine::LoadScenes", "Loading Scene: %s", scene_name.c_str());

        //  Create & Load Scene
        Scene *newScene = new Scene();
        newScene->Load(StringPrintf("%s/%s", resourceFolder.c_str(), scene_name.c_str()).c_str(), renderer);
        // newScene->name = scene_name;

        //  Add Scene to Scenes list
        scenes.push_back(newScene);
    }

    activeScene = scenes.front();

    Log::Instance()->Info("GemEngine::LoadScenes", "Load Scenes Completed");
}

void SceneManager::Clean()
{
    Log::Instance()->Info("SceneManager::Clean", "SceneManager Shutting Down");

    //  Clean up scenes
    for (auto scene : scenes)
    {
        Log::Instance()->Info("GemEngine::~App", "Deleting scene: %s", scene->name.c_str());
        scene->Cleanup();
        delete scene;
    }
    scenes.clear();
}

Scene *SceneManager::GetScene(const string name)
{
    for (auto &&scene : scenes)
    {
        cout << "Checking scene: " << scene->name << endl;
        if (scene->name == name)
        {
            cout << "Found scene: " << name << endl;
            return scene;
        }
    }
    return NULL;
}

void SceneManager::DebugRender(SDL_Renderer *renderer, float time)
{
    Scene *activeScene = SceneManager::Instance()->activeScene;

    // cout << "Render debug" << endl;
    unordered_map<string, GemObject *> objects = activeScene->GetObjects();

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

void SceneManager::Physics(float time)
{
    unordered_map<string, GemObject *> objects = activeScene->GetObjects();

    vector<GemObject *> objects_vector = GetColliderEnabledObjects(objects);

    if (objects_vector.size() == 0)
    {
        return;
    }

    //  Clear collisions
    for (int i = 0; i < objects_vector.size(); i++)
    {
        objects_vector[i]->collisions.clear();
    }

    //  Check collisions
    for (int i = 0; i < objects_vector.size() - 1; i++)
    {
        // cout << "Checking collisions for gemobject: " << objects_vector[i]->name << endl;

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

vector<GemObject *> SceneManager::GetColliderEnabledObjects(unordered_map<string, GemObject *> objects)
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

void SceneManager::RenderActiveScene(float time)
{
    activeScene->Render(time);
}