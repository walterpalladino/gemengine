#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <nlohmann/json.hpp>

#include "core/scenes/Scene.h"

#include "utils/Log.h"
#include "utils/StringUtils.h"

#include "core/exceptions/DuplicatedResourceIdentifier.h"
#include "core/exceptions/ResourceLoadException.h"
#include "core/exceptions/JSONParseException.h"

#include "core/gemobject/GemObject.h"
#include "core/gemobject/GemObjectParser.h"

#include "core/graphics/image/Image.h"
#include "core/graphics/image/ImageParser.h"
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

GemObject *Scene::Add(GemObject *object)
{
    objects[object->id] = object;
}

GemObject *Scene::GetByName(const string name)
{
    for (auto &[id, object] : objects)
    {
        if (object->name.compare(name) == 0)
        {
            return object;
        }
    }
    return nullptr;
}

GemObject *Scene::GetById(const uint64_t id)
{
    if (objects.count(id) != 0)
    {
        return objects[id];
    }
    return nullptr;
}

void Scene::Render(SDL_Renderer *renderer, float time)
{
    //  To sort the objects by z order first we extract them into a vector
    vector<GemObject *> vector_objects;
    for (auto &[name, object] : objects)
    {
        vector_objects.push_back(object);
    }
    sort(vector_objects.begin(), vector_objects.end(), cmp_z_order);
    //  Render scene objects
    for (auto &object : vector_objects)
    {
        object->Render(renderer, time);
    }
}

void Scene::Update(float time)
{
    for (auto &[name, object] : objects)
    {
        object->Update(time);
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

    try
    {

        json data = json::parse(ifstream(fileName.c_str()));
        // cout << config_data << endl;

        //  name is required
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

                GemObject *newObject = new GemObject();
                newObject = GemObjectParser::JSONParse(scene_object);

                Add(newObject);
                /*
                                if (scene_object.contains("type"))
                                {
                                    string type = scene_object.at("type");
                                    if (type == "image")
                                    {
                                        Image *newImage = new Image();
                                        newImage->JSONParse(scene_object);

                                        // Image *newImage = ImageParser::JSONParse(scene_object);
                                        newImage->SetRenderer(renderer);
                                        Add(newImage);
                                    }
                                    else if (type == "text")
                                    {
                                        Text *newText = new Text(renderer);
                                        newText->JSONParse(scene_object);
                                        Add(newText);
                                    }
                                    else if (type == "sprite")
                                    {
                                        Sprite *newSprite = new Sprite(renderer);
                                        newSprite->JSONParse(scene_object);
                                        Add(newSprite);
                                    }
                                    else if (type == "parallax")
                                    {
                                        Parallax *newParallax = new Parallax(renderer);
                                        newParallax->JSONParse(scene_object);
                                        Add(newParallax);
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
                                */
            }
        }
        /*
        else
        {
            Log::Instance()->Error("Scene::Load", "Malformed scene file definition. Missing 'objects' tag.");
            throw JSONParseException("Malformed scene file definition. Missing 'objects' tag.");
        }*/
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
/*
int Scene_Load(string fileName, SDL_Renderer *renderer)
{

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
                        Image *newImage = new Image();
                        newImage->JSONParse(scene_object);

                        // Image *newImage = ImageParser::JSONParse(scene_object);
                        newImage->SetRenderer(renderer);
                        Add(newImage);
                    }
                    else if (type == "text")
                    {
                        Text *newText = new Text(renderer);
                        newText->JSONParse(scene_object);
                        Add(newText);
                    }
                    else if (type == "sprite")
                    {
                        Sprite *newSprite = new Sprite(renderer);
                        newSprite->JSONParse(scene_object);
                        Add(newSprite);
                    }
                    else if (type == "parallax")
                    {
                        Parallax *newParallax = new Parallax(renderer);
                        newParallax->JSONParse(scene_object);
                        Add(newParallax);
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
*/
void Scene::OnMouseButtonDown(SDL_Event &event)
{
    for (auto &[name, object] : objects)
    {
        if (object->enabled)
        {
            object->OnMouseButtonDown(event);
        }
    }
}

void Scene::OnMouseButtonUp(SDL_Event &event)
{
    for (auto &[name, object] : objects)
    {
        if (object->enabled)
        {
            object->OnMouseButtonUp(event);
        }
    }
}

void Scene::OnMouseMove(SDL_Event &event)
{
    for (auto &[name, object] : objects)
    {
        if (object->enabled)
        {
            object->OnMouseMove(event);
        }
    }
}