#include <string>
#include <format>

#include "core/gemobject/GemObjectParser.h"
#include "core/physics/collider/ColliderParser.h"

#include "core/graphics/image/Image.h"
#include "core/graphics/image/ImageParser.h"
#include "core/graphics/sprites/Sprite.h"
#include "core/graphics/sprites/SpriteParser.h"
#include "core/graphics/text/Text.h"
#include "core/graphics/text/TextParser.h"
#include "core/graphics/parallax/Parallax.h"
#include "core/graphics/parallax/ParallaxParser.h"
#include "core/sound/Sound.h"
#include "core/sound/SoundParser.h"
#include "core/sound/Track.h"
#include "core/sound/TrackParser.h"
#include "core/physics/collider/Collider.h"
#include "core/physics/collider/ColliderParser.h"

#include "utils/Log.h"
#include "core/exceptions/JSONParseException.h"

using namespace std;

GemObject *GemObjectParser::JSONParse(json data)
{

    // Get common attributes

    GemObject *object = new GemObject();

    object->name = data["name"];
    object->enabled = data["enabled"];
    object->zOrder = data["z_order"];
    object->layer = data["layer"];

    //  Get Transform
    if (!data.contains("transform"))
    {
        Log::Instance()->Error("GemObjectParser::JSONParse", "Malformed gemobject definition. Missing 'transform' tag.");
        throw JSONParseException("Malformed gemobject definition. Missing 'transform' tag.");
    }
    else
    {
        object->transform = ParseTransform(data.at("transform"));
    }

    //  Get All components
    if (data.contains("components"))
    {

        json json_components = data.at("components");
        for (auto &[key, val] : json_components.items())
        {
            json json_component = val;

            if (json_component.contains("type"))
            {
                string type = json_component.at("type");
                if (type == "image")
                {
                    Image *newImage = ImageParser::JSONParse(json_component);
                    object->AddComponent(newImage);
                }
                else if (type == "sprite")
                {
                    Sprite *newSprite = SpriteParser::JSONParse(json_component);
                    object->AddComponent(newSprite);
                }
                else if (type == "text")
                {
                    Text *newText = TextParser::JSONParse(json_component);
                    object->AddComponent(newText);
                }
                else if (type == "parallax")
                {
                    Parallax *newParallax = ParallaxParser::JSONParse(json_component);
                    object->AddComponent(newParallax);
                }
                else if (type == "collider")
                {
                    Collider *newCollider = ColliderParser::JSONParse(json_component);
                    object->AddComponent(newCollider);
                }
                else if (type == "sound")
                {
                    Sound *newSound = SoundParser::JSONParse(json_component);
                    object->AddComponent(newSound);
                }
                else if (type == "track")
                {
                    Track *newTrack = TrackParser::JSONParse(json_component);
                    object->AddComponent(newTrack);
                }
                else
                {
                    //  Unknown type
                    string error_message = format("Unknown component type: {}.", type);
                    Log::Instance()->Error("GemObjectParser::JSONParse", error_message.c_str());
                    throw JSONParseException(error_message);
                }
            }
            else
            {
                Log::Instance()->Error("GemObjectParser::JSONParse", "Malformed component definition. Missing 'type' tag.");
                throw JSONParseException("Malformed component definition. Missing 'type' tag.");
            }
        }
    }

    return object;
}

Transform GemObjectParser::ParseTransform(json data)
{

    Transform transform;

    json json_position = data.at("position");
    transform.position = Vector3d(json_position.at("x"), json_position.at("y"), json_position.at("z"));

    json json_rotation = data.at("rotation");
    transform.rotation = Vector3d(json_rotation.at("x"), json_rotation.at("y"), json_rotation.at("z"));

    json json_scale = data.at("scale");
    transform.scale = Vector3d(json_scale.at("x"), json_scale.at("y"), json_scale.at("z"));

    return transform;
}