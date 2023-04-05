#include "core/text/Text.h"
#include "utils/Log.h"
#include "core/text/FontsManager.h"

Text::Text(SDL_Renderer *renderer)
{
    Log::GetInstance()->Info("Text::Text", "Constructor");

    this->renderer = renderer;

    text = "";
    fontKey = "";
}

Text::~Text()
{
}

void Text::Cleanup()
{
    Log::GetInstance()->Info("Text::Cleanup", "Cleanup");
}

void Text::Set(const string text, const char *fileName, const int fontSize)
{
    this->fontKey = FontsManager::Instance()->AddFont(fileName, fontSize);

    this->text = text;
}

/*
void Text::Render()
{
    // printf("Image::Render\n");
    //  Update Destination Rectangle based on Position and Scale
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = sourceRect.w * scale.x;
    destRect.h = sourceRect.h * scale.y;

    if (Math::IsZero(rotation.z))
    {
        SDL_RenderCopy(renderer, image, &sourceRect, &destRect);
    }
    else
    {
        SDL_Point center = SDL_Point();
        center.x = destRect.x + destRect.w / 2;
        center.y = destRect.y + destRect.h / 2;

        SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
        SDL_RenderCopyEx(renderer,
                         image,
                         &sourceRect,
                         &destRect,
                         rotation.z,
                         &center,
                         flip);
    }

}
*/