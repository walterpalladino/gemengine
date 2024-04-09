
#include "core/config/Config.h"

#include "core/graphics/image/Image.h"
#include "core/graphics/textures/TextureManager.h"

#include "utils/Log.h"
#include "math/Math.h"

Image::Image()
{
    texture = NULL;
}

Image::~Image()
{
}

void Image::Init()
{
}

void Image::Update(float time)
{
}

void Image::Cleanup()
{
}

void Image::Render(SDL_Renderer *renderer, Transform parentTransform, float time)
{
    if (!enabled)
        return;

    //  Update Destination Rectangle based on Position and Scale
    destRect.x = parentTransform.position.x;
    destRect.y = parentTransform.position.y;
    destRect.w = sourceRect.w * abs(parentTransform.scale.x);
    destRect.h = sourceRect.h * abs(parentTransform.scale.y);

    SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
    if (parentTransform.scale.x < 0)
    {
        flip = (SDL_RendererFlip)(flip | SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
    }
    if (parentTransform.scale.y < 0)
    {
        flip = (SDL_RendererFlip)(flip | SDL_RendererFlip::SDL_FLIP_VERTICAL);
    }

    SDL_RenderCopyEx(renderer,
                     texture,
                     &sourceRect,
                     &destRect,
                     parentTransform.rotation.z,
                     NULL, //&center,
                     flip);
}

void Image::SetTexture(SDL_Texture *texture)
{
    this->texture = texture;

    //  Get texture information
    SDL_QueryTexture(this->texture, NULL, NULL, &sourceRect.w, &sourceRect.h);
}

SDL_Texture *Image::GetTexture()
{
    return texture;
}
