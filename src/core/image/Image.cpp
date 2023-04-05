#include "core/image/Image.h"

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

    // if (image != NULL)
    //{
    //     SDL_FreeSurface(image);
    // }
}

void Image::Load(const char *fileName)
{
    // Load image at specified path
    SDL_Surface *tmp = IMG_Load(fileName);
    if (!tmp)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        char *buffer = new char[512];
        sprintf(buffer, "Unable to load image: %s. SDL Error: %s", fileName, IMG_GetError());

        Log::GetInstance()->Error("Image::Load", buffer);
        throw ResourceLoadException(buffer);
    }

    // Convert surface to screen format
    image = SDL_CreateTextureFromSurface(renderer, tmp);
    if (image == NULL)
    {
        char *buffer = new char[512];
        sprintf(buffer, "Unable to create texture from image: %s. SDL Error: %s", fileName, IMG_GetError());
        Log::GetInstance()->Error("Image::Load", buffer);
        throw ResourceLoadException(buffer);
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(tmp);

    //  Get texture information
    SDL_QueryTexture(image, NULL, NULL, &sourceRect.w, &sourceRect.h);
}

void Image::Render()
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