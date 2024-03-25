#include "core/config/Config.h"

#include "core/graphics/parallax/Parallax.h"
#include "core/graphics/textures/TextureManager.h"

#include "utils/Log.h"
#include "math/Math.h"

Parallax::Parallax(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    image = NULL;
    offset = Point2dInt(0, 0);
}

Parallax::~Parallax()
{
}

void Parallax::Init()
{
}

void Parallax::Update(float time)
{
}

void Parallax::Cleanup()
{
}

void Parallax::Load(const char *fileName)
{
    image = TextureManager::Instance()->Add(fileName);
    //  Get texture information
    SDL_QueryTexture(image, NULL, NULL, &sourceRect.w, &sourceRect.h);
}

void Parallax::Render(float time)
{
    if (!enabled)
        return;

    SDL_Rect fromRect;

    offset.x = offset.x % sourceRect.w;
    offset.y = offset.y % sourceRect.h;

    fromRect = sourceRect;

    fromRect.w -= abs(offset.x);

    destRect.x = position.x;
    destRect.y = position.y;
    destRect.w = sourceRect.w * abs(scale.x);
    destRect.w -= abs(offset.x);
    destRect.h = sourceRect.h * abs(scale.y);

    if (offset.x >= 0)
    {
        fromRect.x += offset.x;
    }
    else
    {
        destRect.x -= offset.x;
    }

    SDL_RenderCopy(renderer,
                   image,
                   &fromRect,
                   &destRect);

    if (offset.x != 0)
    {
        fromRect = sourceRect;

        fromRect.w = abs(offset.x);

        destRect.y = position.y;
        destRect.h = sourceRect.h * abs(scale.y);
        destRect.w = abs(offset.x);
        destRect.h = sourceRect.h * abs(scale.y);

        if (offset.x > 0)
        {
            destRect.x = sourceRect.w * abs(scale.x) - offset.x;
        }
        else
        {
            fromRect.x = sourceRect.w * abs(scale.x) + offset.x;

            destRect.x = position.x;
        }

        SDL_RenderCopy(renderer,
                       image,
                       &fromRect,
                       &destRect);
    }
}

void Parallax::JSONParse(json data)
{
    GemObject::JSONParse(data);

    Init();

    string src = data.at("src");
    string src_file = Config::Instance()->config_data.resource_folder + "/" + src;

    Load(src_file.c_str());

    // json json_speed = data.at("speed");
    // speed = Point2dInt(json_speed.at("x"), json_speed.at("y"));
}