#include <string>

#include "core/graphics/console/Console.h"
#include "core/graphics/textures/TextureManager.h"
#include "core/graphics/text/FontsManager.h"

#include "utils/Log.h"
#include "exceptions/ResourceLoadException.h"
#include "math/Math.h"

Console *Console::instance = 0;

//  Point2dInt(48, 27);
void Console::Init(SDL_Renderer *renderer, int x, int y, int width, int height, const char *fileName, const int fontSize)
{
    Log::GetInstance()->Info("Console::Init", "Initializing");

    this->renderer = renderer;
    // image = NULL;
    position.x = x;
    position.y = y;
    virtualConsoleSize = Point2dInt(width, height);

    this->font = FontsManager::Instance()->Add(fileName, fontSize);

    consoleBuffer = new char[width * height];
    sprintf(consoleBuffer, "GemEngine running...");

    characterSize = Point2dInt(fontSize, fontSize);

    enabled = true;
}

void Console::Cleanup()
{
    Log::GetInstance()->Info("Console::Cleanup", "Cleanup");

    if (consoleBuffer != NULL)
    {
        delete (consoleBuffer);
    }
}

void Console::Render(float time)
{
    for (int c = 0; c < virtualConsoleSize.x * virtualConsoleSize.y; c++)
    {
        int x = c % virtualConsoleSize.x;
        int y = c / virtualConsoleSize.x;
        DrawCharacterAt(x, y, consoleBuffer[c]);
    }
}

void Console::DrawCharacterAt(int x, int y, char c)
{

    char *buffer = new char[1];
    buffer[0] = c;
    // buffer[1] = '\0';

    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, buffer, color);

    //  Update Destination Rectangle based on Position and Scale
    destRect.x = x * characterSize.x;
    destRect.y = y * characterSize.y;
    destRect.w = characterSize.x;
    destRect.h = characterSize.y;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopyEx(renderer,
                     texture,
                     NULL,
                     &destRect,
                     0,
                     NULL,
                     SDL_RendererFlip::SDL_FLIP_NONE);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
