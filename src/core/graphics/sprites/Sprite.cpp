#include "core/graphics/sprites/Sprite.h"
#include "core/config/Config.h"

#include "utils/Log.h"
#include "math/Math.h"

#include "core/exceptions/ResourceLoadException.h"

Sprite::Sprite(SDL_Renderer *renderer)
{
    this->renderer = renderer;
}

Sprite::~Sprite()
{
}

void Sprite::Init()
{
}

void Sprite::Update(float time)
{
    if (!enabled)
        return;

    if (animations.size() == 0)
        return;

    if ((actualAnimation < 0) || (actualAnimation >= animations.size()))
        return;

    animations[actualAnimation].Update(time);
}

void Sprite::Cleanup()
{
}

void Sprite::Render(float time)
{
    if (!enabled)
        return;

    //  Adjust source of the sprite to draw
    SDL_Rect spriteSourceRect = SDL_Rect();
    spriteSourceRect.x = animations[actualAnimation].offset.x + animations[actualAnimation].actualFrame * animations[actualAnimation].size.x;
    spriteSourceRect.y = animations[actualAnimation].offset.y;
    spriteSourceRect.w = animations[actualAnimation].size.x;
    spriteSourceRect.h = animations[actualAnimation].size.y;

    //  Update Destination Rectangle based on Position and Scale
    destRect.x = transform.position.x;
    destRect.y = transform.position.y;
    destRect.w = animations[actualAnimation].size.x * abs(transform.scale.x);
    destRect.h = animations[actualAnimation].size.y * abs(transform.scale.y);

    SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
    if (transform.scale.x < 0)
    {
        flip = (SDL_RendererFlip)(flip | SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
    }
    if (transform.scale.y < 0)
    {
        flip = (SDL_RendererFlip)(flip | SDL_RendererFlip::SDL_FLIP_VERTICAL);
    }

    SDL_RenderCopyEx(renderer,
                     animations[actualAnimation].image,
                     &spriteSourceRect,
                     &destRect,
                     transform.rotation.z,
                     NULL, //&center,
                     flip);

    RenderCollider(renderer, {255, 255, 0, 255});
}

void Sprite::JSONParse(json data)
{
    GemObject::JSONParse(data);

    Init();

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

            animations.push_back(animation);
        }

        actualAnimation = 0;
    }
    else
    {
        Log::Instance()->Error("Sprite::JSONParse", "No animations found in JSON");
        throw ResourceLoadException("Sprite: No animations found in JSON");
    }
}

void Sprite::AddAnimation(Animation animation)
{
    animations.push_back(animation);
}

Animation Sprite::GetAnimation(int index)
{
    return animations[index];
}

int Sprite::GetActualAnimation()
{
    return actualAnimation;
}

void Sprite::SetActualAnimation(int actualAnimation)
{
    if ((actualAnimation < 0) || (actualAnimation >= animations.size()))
        return;
    this->actualAnimation = actualAnimation;

    sourceRect.w = animations[actualAnimation].textureWidth;
    sourceRect.h = animations[actualAnimation].textureHeight;
}