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

    // this->font = FontsManager::Instance()->Add(fileName, fontSize);
    LoadFont(fileName);

    characterSize = Point2dInt(fontSize, fontSize);

    consoleBuffer = new char[width * height];

    Clear();

    // sprintf(consoleBuffer, "GemEngine running...");
    const char text[] = "GemEngine running...";
    std::copy(text, text + sizeof(text), consoleBuffer);

    enabled = true;
}

void Console::LoadFont(const char *fileName)
{
    fontTexture = TextureManager::Instance()->Add(fileName);
    //  Get texture information
    SDL_QueryTexture(fontTexture, NULL, NULL, &textureRect.w, &textureRect.h);
    // printf("%i - %i\n", textureRect.w, textureRect.h);
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
    // for (int c = 0; c < 1; c++)
    {
        int x = c % virtualConsoleSize.x;
        int y = c / virtualConsoleSize.x;
        DrawCharacterAt(x, y, consoleBuffer[c]);
    }
}

void Console::DrawCharacterAt(int x, int y, char c)
{

    // char *buffer = new char[1];
    // buffer[0] = c;
    //  buffer[1] = '\0';

    SDL_Color color = {255, 255, 255};
    // SDL_Surface *surface = TTF_RenderText_Solid(font, buffer, color);
    SDL_Rect srcRect;
    SDL_Rect destRect;

    int start = ((int)c) * characterSize.x;

    // printf("x:%i - y:%i - c:%i\n", x, y, c);

    //  Set Source
    srcRect.x = start % textureRect.w;
    srcRect.y = start / textureRect.w * characterSize.y;
    srcRect.w = characterSize.x;
    srcRect.h = characterSize.y;

    // printf("srcRect.x:%i - srcRect.y:%i - srcRect.w:%i - srcRect.h:%i\n", srcRect.x, srcRect.y, srcRect.w, srcRect.h);

    //  Set Destination Rectangle
    destRect.x = x * characterSize.x;
    destRect.y = y * characterSize.y;
    destRect.w = characterSize.x;
    destRect.h = characterSize.y;

    SDL_RenderCopyEx(renderer,
                     fontTexture,
                     &srcRect,
                     &destRect,
                     0,
                     NULL,
                     SDL_RendererFlip::SDL_FLIP_NONE);
}

void Console::Clear()
{
    std::fill(consoleBuffer, consoleBuffer + virtualConsoleSize.x * virtualConsoleSize.y, ' ');
}