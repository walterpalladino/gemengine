#include "core/graphics/sprites/Sprite.h"
#include "core/graphics/textures/TextureManager.h"

#include "utils/Log.h"
#include "exceptions/ResourceLoadException.h"
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

void Sprite::Load(const char *fileName)
{
    image = TextureManager::Instance()->Add(fileName);
    //  Get texture information
    SDL_QueryTexture(image, NULL, NULL, &sourceRect.w, &sourceRect.h);
}

void Sprite::Render()
{

    //  Update Destination Rectangle based on Position and Scale
    destRect.x = position.x;
    destRect.y = position.y;
    destRect.w = sourceRect.w * scale.x;
    destRect.h = sourceRect.h * scale.y;

    if (Math::IsZero(rotation.z))
    {
        SDL_RenderCopy(renderer, image, &sourceRect, &destRect);
    }
    else
    {
        SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
        SDL_RenderCopyEx(renderer,
                         image,
                         &sourceRect,
                         &destRect,
                         rotation.z,
                         NULL, //&center,
                         flip);
    }
}
