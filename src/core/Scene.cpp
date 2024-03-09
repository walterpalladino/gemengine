#include <iostream>
#include <fstream>
#include <chrono>
#include <nlohmann/json.hpp>

#include "core/Scene.h"

#include "utils/Log.h"
#include "utils/StringUtils.h"

#include "core/graphics/console/Console.h"

#include "core/exceptions/DuplicatedResourceIdentifier.h"
#include "core/exceptions/ResourceLoadException.h"

#include "core/graphics/image/Image.h"
#include "core/graphics/sprites/Sprite.h"
#include "core/graphics/text/Text.h"

using json = nlohmann::json;
using namespace std;

// Scene::Scene(SDL_Renderer *renderer)
Scene::Scene()
{
    Log::GetInstance()->Info("Scene::Scene", "Constructor");
    // this->renderer = renderer;
    // objects.reserve(MAX_OBJECTS_PER_SCENE);
}

Scene::~Scene()
{
    Log::GetInstance()->Info("Scene::~Scene", "Destructor");
}

GemObject *Scene::Add(const char *name, GemObject *object)
{
    //  Check if there is an object with the same name
    if (objects.count(name) != 0)
    {
        printf("Scene::Add - Duplicate Identifier %s\n", name);
        char *buffer = new char[512];
        sprintf(buffer, "Duplicate Identifier: %s.", name);

        Log::GetInstance()->Error("Scene::Add", buffer);
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

    Console::Instance()->Render(time);

    //  Render scene objects
    for (auto &[name, object] : objects)
    {
        object->Render(time);
    }
}

void Scene::Cleanup()
{
    Log::GetInstance()->Info("Scene::Cleanup", "Cleanup");

    //  Clean up scene objects
    for (auto &[name, object] : objects)
    {
        Log::GetInstance()->Info("Scene::Cleanup", "Deleting object: %s", object->name.c_str());
        object->Cleanup();
        delete object;
    }
    objects.clear();
}

int Scene::Load(string fileName, SDL_Renderer *renderer, string resourceFolder)
{

    try
    {

        json data = json::parse(ifstream(fileName.c_str()));
        // cout << config_data << endl;
        if (data.contains("name"))
        {
            name = data.at("name");
        }

        if (data.contains("objects"))
        {
            json scene_objects = data.at("objects");

            // for (json::iterator it = scene_objects.begin(); it != scene_objects.end(); ++it)
            for (auto &[key, val] : scene_objects.items())
            {
                // cout << key << ": " << val << endl;
                //                 cout << scene_objects[key] << endl;
                json scene_object = val;
                if (scene_object.contains("type"))
                {
                    string type = scene_object.at("type");
                    if (type == "image")
                    {

                        //  Create Image
                        Image *newImage = new Image(renderer);
                        newImage->Init();

                        string name = scene_object.at("name");
                        newImage->name = string(name);

                        //  Load Image
                        string src = scene_object.at("src");
                        newImage->Load(StringPrintf("%s/%s", resourceFolder.c_str(), src.c_str()).c_str());

                        newImage->enabled = scene_object.at("enabled");

                        json json_position = scene_object.at("position");
                        newImage->position = Vector3d(json_position.at("x"), json_position.at("y"), json_position.at("z"));

                        json json_rotation = scene_object.at("rotation");
                        newImage->rotation = Vector3d(json_rotation.at("x"), json_rotation.at("y"), json_rotation.at("z"));

                        json json_scale = scene_object.at("scale");
                        newImage->scale = Vector3d(json_scale.at("x"), json_scale.at("y"), json_scale.at("z"));

                        //   Add Image to Scene
                        Add(name.c_str(), newImage);
                    }
                    else if (type == "text")
                    {
                        //  Create Image
                        Text *newText = new Text(renderer);
                        newText->Init();

                        string name = scene_object.at("name");
                        newText->name = string(name);

                        //  Load Image
                        string src = scene_object.at("src");
                        newText->Init("SDL2 text", StringPrintf("%s/%s", resourceFolder.c_str(), src.c_str()).c_str(), 24);

                        newText->enabled = scene_object.at("enabled");

                        json json_position = scene_object.at("position");
                        newText->position = Vector3d(json_position.at("x"), json_position.at("y"), json_position.at("z"));

                        json json_rotation = scene_object.at("rotation");
                        newText->rotation = Vector3d(json_rotation.at("x"), json_rotation.at("y"), json_rotation.at("z"));

                        json json_scale = scene_object.at("scale");
                        newText->scale = Vector3d(json_scale.at("x"), json_scale.at("y"), json_scale.at("z"));

                        //   Add Image to Scene
                        Add(name.c_str(), newText);
                    }
                    else if (type == "sprite")
                    {
                        //  Create Image
                        Sprite *newSprite = new Sprite(renderer);

                        string name = scene_object.at("name");
                        newSprite->name = string(name);

                        //  Load Image
                        string src = scene_object.at("src");

                        json json_offset = scene_object.at("offset");
                        int offsetX = json_offset.at("x");
                        int offsetY = json_offset.at("y");

                        json json_size = scene_object.at("size");
                        int width = json_size.at("x");
                        int height = json_size.at("y");

                        int frames = scene_object.at("frames");
                        int speed = scene_object.at("speed");

                        newSprite->Load(StringPrintf("%s/%s", resourceFolder.c_str(), src.c_str()).c_str(), offsetX, offsetY, width, height, frames, speed);

                        newSprite->enabled = scene_object.at("enabled");

                        json json_position = scene_object.at("position");
                        newSprite->position = Vector3d(json_position.at("x"), json_position.at("y"), json_position.at("z"));

                        json json_rotation = scene_object.at("rotation");
                        newSprite->rotation = Vector3d(json_rotation.at("x"), json_rotation.at("y"), json_rotation.at("z"));

                        json json_scale = scene_object.at("scale");
                        newSprite->scale = Vector3d(json_scale.at("x"), json_scale.at("y"), json_scale.at("z"));

                        //   Add Image to Scene
                        Add(name.c_str(), newSprite);
                    }
                    else
                    {
                        //  Unknown type
                        cout << "Unknown type: " << type << endl;
                    }
                }
                // cout << scene_object << endl;
                // GemObject *object = GemObject::Create(it.value());
                // Add(it.key().c_str(), object);
            }
        }
    }
    catch (std::exception &e)
    {
        cout << e.what() << endl;
        char *buffer = new char[512];
        sprintf(buffer, "Unable to load scene file: %s.", fileName.c_str());

        Log::GetInstance()->Error("Scene::Load", buffer);
        throw ResourceLoadException(buffer);
    }

    return 0;
}