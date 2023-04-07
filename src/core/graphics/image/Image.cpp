#include "core/graphics/image/Image.h"
#include "core/graphics/textures/TextureManager.h"

#include "utils/Log.h"
#include "exceptions/ResourceLoadException.h"
#include "math/Math.h"

Image::Image(SDL_Renderer *renderer)
{
    Log::GetInstance()->Info("Image::Image", "Constructor");

    this->renderer = renderer;
    image = NULL;
}

Image::~Image()
{
}

void Image::Init()
{
}

void Image::Update()
{
}

void Image::Cleanup()
{
    Log::GetInstance()->Info("Image::Cleanup", "Cleanup");
}

void Image::Load(const char *fileName)
{
    image = TextureManager::Instance()->Add(fileName);
    //  Get texture information
    SDL_QueryTexture(image, NULL, NULL, &sourceRect.w, &sourceRect.h);
}

void Image::Render(float time)
{

    // printf("Image::Render\n");
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
    { /*
         SDL_Point center = SDL_Point();
         center.x = destRect.x + destRect.w / 2;
         center.y = destRect.y + destRect.h / 2;
 */
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