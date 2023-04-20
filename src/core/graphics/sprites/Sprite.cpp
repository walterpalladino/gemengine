#include "core/graphics/sprites/Sprite.h"
#include "core/graphics/textures/TextureManager.h"

#include "utils/Log.h"
#include "core/exceptions/ResourceLoadException.h"
#include "math/Math.h"

Sprite::Sprite(SDL_Renderer *renderer)
{
    Log::GetInstance()->Info("Sprite::Sprite", "Constructor");

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
    Log::GetInstance()->Info("Image::Cleanup", "Cleanup");
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
}
