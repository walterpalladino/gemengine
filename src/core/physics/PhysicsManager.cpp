
#include <SDL2/SDL.h>

#include "core/physics/PhysicsManager.h"
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"

using namespace std;

void PhysicsManager::Physics(float time)
{
    Scene *activeScene = SceneManager::Instance()->activeScene;

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
        for (int j = i + 1; j < objects_vector.size(); j++)
        {
            SDL_Rect AABBi = objects_vector[i]->GetColliderRect();
            SDL_Rect AABBj = objects_vector[j]->GetColliderRect();
            SDL_Rect *AABBcollision = new SDL_Rect();

            bool status = SDL_IntersectRect(&AABBi, &AABBj, AABBcollision);
            if (status)
            {
                objects_vector[i]->collisions[objects_vector[j]->name] = *AABBcollision;
                objects_vector[j]->collisions[objects_vector[i]->name] = *AABBcollision;
            }

            delete AABBcollision;
        }
    }
}

vector<GemObject *> PhysicsManager::GetColliderEnabledObjects(unordered_map<string, GemObject *> objects)
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

void PhysicsManager::DebugRender(SDL_Renderer *renderer, float time)
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