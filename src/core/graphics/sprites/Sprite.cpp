#include "core/graphics/sprites/Sprite.h"
#include "core/graphics/textures/TextureManager.h"
#include "core/Config.h"

#include "utils/Log.h"
#include "math/Math.h"

Sprite::Sprite(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    image = NULL;
}

Sprite::~Sprite()
{
}

void Sprite::Init()
{
}

void Sprite::Update()
{
}

void Sprite::Cleanup()
{
}

void Sprite::Load(const char *fileName, int offsetX, int offsetY, int width, int height, int frames, int speed)
{
    offset.x = offsetX;
    offset.y = offsetY;

    size.x = width;
    size.y = height;

    animationFrames = frames;
    animationSpeed = speed;

    image = TextureManager::Instance()->Add(fileName);
    //  Get texture information
    SDL_QueryTexture(image, NULL, NULL, &sourceRect.w, &sourceRect.h);

    actualFrame = 0;
    animationStartTime = -1;
}

void Sprite::Render(float time)
{
    if (!enabled)
        return;

    if (animationStartTime == -1)
    {
        //  First call
        animationStartTime = time;
    }

    //  Calculate the ctual frame based on speed of animation and number of frames
    actualFrame = time - animationStartTime;
    actualFrame *= animationSpeed;
    actualFrame /= 1000;
    actualFrame %= animationFrames;

    //  Adjust source of the sprite to draw
    SDL_Rect spriteSourceRect = SDL_Rect();
    spriteSourceRect.x = offset.x + actualFrame * size.x;
    spriteSourceRect.y = offset.y;
    spriteSourceRect.w = size.x;
    spriteSourceRect.h = size.y;

    //  Update Destination Rectangle based on Position and Scale
    destRect.x = position.x;
    destRect.y = position.y;
    destRect.w = size.x * abs(scale.x);
    destRect.h = size.y * abs(scale.y);

    SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
    if (scale.x < 0)
    {
        flip = (SDL_RendererFlip)(flip | SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
    }
    if (scale.y < 0)
    {
        flip = (SDL_RendererFlip)(flip | SDL_RendererFlip::SDL_FLIP_VERTICAL);
    }

    SDL_RenderCopyEx(renderer,
                     image,
                     &spriteSourceRect,
                     &destRect,
                     rotation.z,
                     NULL, //&center,
                     flip);

    RenderCollider(renderer, {255, 255, 0, 255});
}

void Sprite::JSONParse(json data)
{
    GemObject::JSONParse(data);

    Init();

    string src = data.at("src");
    string src_file = Config::Instance()->config_data.resource_folder + "/" + src;

    json json_offset = data.at("offset");
    int offsetX = json_offset.at("x");
    int offsetY = json_offset.at("y");

    json json_size = data.at("size");
    int width = json_size.at("x");
    int height = json_size.at("y");

    int frames = data.at("frames");
    int speed = data.at("speed");

    Load(src_file.c_str(), offsetX, offsetY, width, height, frames, speed);
}
