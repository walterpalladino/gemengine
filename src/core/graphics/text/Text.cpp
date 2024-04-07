#include "core/graphics/text/Text.h"
#include "core/graphics/text/FontsManager.h"
#include "core/config/Config.h"

#include "utils/Log.h"
#include "math/Math.h"

Text::Text(SDL_Renderer *renderer)
{
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

void Text::Update(float time)
{
}

void Text::Cleanup()
{
}

void Text::Init(const string text, const char *fileName, const int fontSize)
{
    this->font = FontsManager::Instance()->Add(fileName, fontSize);
    this->text = text;
}

void Text::Render(float time)
{

    if (!enabled)
        return;

    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);

    //  Update Destination Rectangle based on Position and Scale
    destRect.x = transform.position.x;
    destRect.y = transform.position.y;
    destRect.w = surface->w * transform.scale.x;
    destRect.h = surface->h * transform.scale.y;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (Math::IsZero(transform.rotation.z))
    {
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
    }
    else
    {
        SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
        SDL_RenderCopyEx(renderer,
                         texture,
                         NULL,
                         &destRect,
                         transform.rotation.z,
                         NULL, //&center,
                         flip);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Text::JSONParse(json data)
{
    GemObject::JSONParse(data);

    Init();

    string src = data.at("src");
    string src_file = Config::Instance()->config_data.resource_folder + "/" + src;

    Init("SDL2 text", src_file.c_str(), 24);
}
