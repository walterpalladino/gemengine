#include "core/graphics/text/Text.h"
#include "core/graphics/text/FontsManager.h"
#include "utils/Log.h"
#include "math/Math.h"

Text::Text(SDL_Renderer *renderer)
{
    Log::GetInstance()->Info("Text::Text", "Constructor");

    this->renderer = renderer;

    text = "";
    font = NULL;
}

Text::~Text()
{
}

void Text::Init()
{
}

void Text::Update()
{
}

void Text::Cleanup()
{
    Log::GetInstance()->Info("Text::Cleanup", "Cleanup");
}

void Text::Init(const string text, const char *fileName, const int fontSize)
{
    this->font = FontsManager::Instance()->Add(fileName, fontSize);
    this->text = text;
}

void Text::Render(float time)
{
    // printf("Text::Render\n");

    if (!enabled)
        return;

    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);

    //  Update Destination Rectangle based on Position and Scale
    destRect.x = position.x;
    destRect.y = position.y;
    destRect.w = surface->w * scale.x;
    destRect.h = surface->h * scale.y;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (Math::IsZero(rotation.z))
    {
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
    }
    else
    { /*
         SDL_Point center = SDL_Point();
         center.x = destRect.x + destRect.w / 2;
         center.y = destRect.y + destRect.h / 2;
 */
        SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
        SDL_RenderCopyEx(renderer,
                         texture,
                         NULL,
                         &destRect,
                         rotation.z,
                         NULL, //&center,
                         flip);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
