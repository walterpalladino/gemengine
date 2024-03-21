#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <nlohmann/json.hpp>

#include "core/scenes/Scene.h"
#include "core/Config.h"

#include "utils/Log.h"
#include "utils/StringUtils.h"

#include "core/exceptions/DuplicatedResourceIdentifier.h"
#include "core/exceptions/ResourceLoadException.h"
#include "core/exceptions/JSONParseException.h"

#include "core/graphics/image/Image.h"
#include "core/graphics/sprites/Sprite.h"
#include "core/graphics/text/Text.h"
#include "core/graphics/parallax/Parallax.h"
#include "core/sound/SoundManager.h"

using json = nlohmann::json;
using namespace std;

bool cmp_z_order(GemObject *a, GemObject *b)
{
    return a->zOrder > b->zOrder;
}

// Scene::Scene(SDL_Renderer *renderer)
Scene::Scene()
{
    Log::Instance()->Info("Scene::Scene", "Constructor");
}

Scene::~Scene()
{
    Log::Instance()->Info("Scene::~Scene", "Destructor");
}

GemObject *Scene::Add(const char *name, GemObject *object)
{
    //  Check if there is an object with the same name
    if (objects.count(name) != 0)
    {
        // printf("Scene::Add - Duplicate Identifier %s\n", name);
        char *buffer = new char[512];
        sprintf(buffer, "Duplicate Identifier: %s.", name);

        Log::Instance()->Error("Scene::Add", buffer);
        throw DuplicatedResourceIdentifier(buffer);
    }

    objects[name] = object;
}

GemObject *Scene::Get(const char *name)
{
    return objects[name];
}

void Scene::Render(float time)
{
    //  To sort the objects by layer first we extract them into a vector
    vector<GemObject *> vector_objects;
    for (auto &[name, object] : objects)
    {
        vector_objects.push_back(object);
    }
    sort(vector_objects.begin(), vector_objects.end(), cmp_z_order);
    for (auto &object : vector_objects)
    {
        object->Render(time);
    }
}

void Scene::Cleanup()
{
    Log::Instance()->Info("Scene::Cleanup", "Cleanup");

    //   Clean up scene objects
    for (auto &[name, object] : objects)
    {
        Log::Instance()->Info("Scene::Cleanup", "Deleting object: %s", object->name.c_str());
        object->Cleanup();
        delete object;
    }
    objects.clear();
}

int Scene::Load(string fileName, SDL_Renderer *renderer)
{

    string resourceFolder = Config::Instance()->config_data.resource_folder;
    try
    {

        json data = json::parse(ifstream(fileName.c_str()));
        // cout << config_data << endl;
        if (data.contains("name"))
        {
            name = data.at("name");
        }
        else
        {
            Log::Instance()->Error("Scene::Load", "Malformed scene file definition. Missing 'name' tag.");
            throw JSONParseException("Malformed scene file definition. Missing 'name' tag.");
        }

        if (data.contains("objects"))
        {
            json scene_objects = data.at("objects");

            for (auto &[key, val] : scene_objects.items())
            {
                json scene_object = val;
                if (scene_object.contains("type"))
                {
                    string type = scene_object.at("type");
                    if (type == "image")
                    {
                        Image *newImage = new Image(renderer);
                        newImage->JSONParse(scene_object);
                        Add(newImage->name.c_str(), newImage);
                    }
                    else if (type == "text")
                    {
                        Text *newText = new Text(renderer);
                        newText->JSONParse(scene_object);
                        Add(newText->name.c_str(), newText);
                    }
                    else if (type == "sprite")
                    {
                        Sprite *newSprite = new Sprite(renderer);
                        newSprite->JSONParse(scene_object);
                        Add(newSprite->name.c_str(), newSprite);
                    }
                    else if (type == "parallax")
                    {
                        Parallax *newParallax = new Parallax(renderer);
                        newParallax->JSONParse(scene_object);
                        Add(newParallax->name.c_str(), newParallax);
                    }
                    else if (type == "sound")
                    {
                        SoundManager::Instance()->JSONParseSound(scene_object);
                    }
                    else if (type == "track")
                    {
                        SoundManager::Instance()->JSONParseTrack(scene_object);
                    }
                    else
                    {
                        //  Unknown type
                        char *buffer = new char[512];
                        sprintf(buffer, "Unknown type: %s.", type.c_str());

                        Log::Instance()->Error("Scene::Load", buffer);
                        throw ResourceLoadException(buffer);
                    }
                }
            }
        }
        else
        {
            Log::Instance()->Error("Scene::Load", "Malformed scene file definition. Missing 'objects' tag.");
            throw JSONParseException("Malformed scene file definition. Missing 'objects' tag.");
        }
    }
    catch (std::exception &e)
    {
        // cout << e.what() << endl;
        char *buffer = new char[512];
        sprintf(buffer, "Unable to load scene file: %s.", fileName.c_str());

        Log::Instance()->Error("Scene::Load", buffer);
        throw JSONParseException(buffer);
    }

    return 0;
}