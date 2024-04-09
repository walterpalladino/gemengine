
#include <SDL2/SDL.h>

#include "core/physics/PhysicsEngine.h"
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"

using namespace std;

void PhysicsEngine::Physics(float time)
{
    Scene *activeScene = SceneManager::Instance()->activeScene;

    unordered_map<uint64_t, GemObject *> objects = activeScene->GetObjects();

    vector<GemObject *> objects_vector = GetColliderEnabledObjects(objects);

    if (objects_vector.size() == 0)
    {
        return;
    }

    //  Clear collisions
    for (int i = 0; i < objects_vector.size(); i++)
    {
        objects_vector[i]->collider.collisions.clear();
    }

    //  Check collisions
    for (int i = 0; i < objects_vector.size() - 1; i++)
    {
        if (!objects_vector[i]->enabled)
        {
            continue;
        }

        for (int j = i + 1; j < objects_vector.size(); j++)
        {

            if (!objects_vector[j]->enabled)
            {
                continue;
            }

            SDL_Rect AABBi = objects_vector[i]->GetColliderRect();
            SDL_Rect AABBj = objects_vector[j]->GetColliderRect();
            SDL_Rect *AABBcollision = new SDL_Rect();

            bool status = SDL_IntersectRect(&AABBi, &AABBj, AABBcollision);
            if (status)
            {
                if (objects_vector[i]->collider.mask & objects_vector[j]->layer)
                {
                    objects_vector[i]->collider.collisions[objects_vector[j]->id] = *AABBcollision;
                }
                if (objects_vector[j]->collider.mask & objects_vector[i]->layer)
                {
                    objects_vector[j]->collider.collisions[objects_vector[i]->id] = *AABBcollision;
                }
            }

            delete AABBcollision;
        }
    }
}

vector<GemObject *> PhysicsEngine::GetColliderEnabledObjects(unordered_map<uint64_t, GemObject *> objects)
{

    vector<GemObject *> objects_vector;

    for (auto &[id, object] : objects)
    {
        if (object->enabled && object->collider.enabled)
        {
            objects_vector.push_back(object);
        }
    }

    return objects_vector;
}

void PhysicsEngine::DebugRender(SDL_Renderer *renderer, float time)
{
    Scene *activeScene = SceneManager::Instance()->activeScene;

    // cout << "Render debug" << endl;
    unordered_map<uint64_t, GemObject *> objects = activeScene->GetObjects();

    //  Render scene objects
    for (auto &[id, object] : objects)
    {
        if (object->enabled && object->collider.enabled)
        {
            // cout << "Checking : " << object->collisions.size() << " collisions for gemobject: " << object->name << endl;
            if (object->collider.collisions.size() > 0)
            {
                // cout << "Drawing collisions for gemobject: " << object->name << endl;
                //   Render collisions
                for (auto &[id, collision] : object->collider.collisions)
                {
                    object->RenderCollisionRect(renderer, id, {255, 0, 0, 255});
                }
            }
        }
    }
}