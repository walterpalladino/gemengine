#include "core/graphics/sprites/SpriteParser.h"
#include "core/graphics/textures/TextureManager.h"
#include "core/config/Config.h"

#include "utils/Log.h"
#include "core/exceptions/ResourceLoadException.h"

Sprite *SpriteParser::JSONParse(json data)
{
    Sprite *sprite = new Sprite();

    if (data.contains("animations"))
    {
        json sprite_animations = data.at("animations");

        if (sprite_animations.size() == 0)
        {
            Log::Instance()->Error("Sprite::JSONParse", "No animations found in JSON");
            throw ResourceLoadException("Sprite: No animations found in JSON");
        }

        for (auto &[key, val] : sprite_animations.items())
        {
            json animation_data = val;
            Animation animation;
            animation.JSONParse(animation_data);

            sprite->AddAnimation(animation);
        }

        sprite->SetActualAnimation(0);
    }
    else
    {
        Log::Instance()->Error("Sprite::JSONParse", "No animations found in JSON");
        throw ResourceLoadException("Sprite: No animations found in JSON");
    }

    return sprite;
}
