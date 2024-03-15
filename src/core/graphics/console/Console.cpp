#include <iostream>
#include <string>

#include "core/graphics/console/Console.h"
#include "core/graphics/textures/TextureManager.h"
#include "core/graphics/text/FontsManager.h"

#include "utils/Log.h"
#include "core/Config.h"
#include "core/exceptions/ResourceLoadException.h"
#include "math/Math.h"

using namespace std;

Console *Console::instance = 0;

void Console::Init(SDL_Renderer *renderer)
{
    this->renderer = renderer;

    enabled = Config::Instance()->config_data.console_enabled;

    if (enabled)
    {
        string resourceFolder = Config::Instance()->config_data.resource_folder;
        string fontFileName = resourceFolder + "/" + Config::Instance()->config_data.console_font;

        Init(renderer, Config::Instance()->config_data.console_x,
             Config::Instance()->config_data.console_y,
             Config::Instance()->config_data.console_width,
             Config::Instance()->config_data.console_height,
             fontFileName.c_str(),
             Config::Instance()->config_data.console_font_size);

        Log::GetInstance()->Info("Console::Init", "Console initialized");
    }
}

void Console::Init(SDL_Renderer *renderer, int x, int y, int width, int height, const char *fileName, const int fontSize)
{
    Log::GetInstance()->Info("Console::Init", "Initializing");

    this->renderer = renderer;

    position.x = x;
    position.y = y;
    virtualConsoleSize = Point2dInt(width, height);

    LoadFont(fileName);

    characterSize = Point2dInt(fontSize, fontSize);

    consoleBuffer = new char[width * height];

    color = Point3dInt(255, 255, 255);

    Clear();

    enabled = true;
}

void Console::LoadFont(const char *fileName)
{
    Log::GetInstance()->Info("Console::LoadFont", "Loading font : %s", fileName);
    fontTexture = TextureManager::Instance()->Add(fileName);
    //  Get texture information
    SDL_QueryTexture(fontTexture, NULL, NULL, &textureRect.w, &textureRect.h);
}

void Console::Cleanup()
{
    Log::GetInstance()->Info("Console::Cleanup", "Cleanup");

    if (consoleBuffer != NULL)
    {
        delete (consoleBuffer);
        consoleBuffer = NULL;
    }
}

void Console::Render(float time)
{
    if (!enabled)
        return;

    for (int c = 0; c < virtualConsoleSize.x * virtualConsoleSize.y; c++)
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

    // SDL_Color color = {255, 255, 255};
    //  SDL_Surface *surface = TTF_RenderText_Solid(font, buffer, color);
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

    SDL_SetTextureColorMod(fontTexture,
                           color.x, color.y, color.z);

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
    SetCursorAt(0, 0);
}

void Console::SetCursorAt(int x, int y)
{
    cursorPosition = Point2dInt(x, y);
}

const Point2dInt Console::GetCursorPosition()
{
    return cursorPosition;
}

void Console::PutCharacterAt(int x, int y, char c)
{
    if (x >= 0 && x < virtualConsoleSize.x && y >= 0 && y < virtualConsoleSize.y)
    {
        SetCharacterAt(x, y, c);
    }
}

void Console::SetCharacterAt(int x, int y, char c)
{
    consoleBuffer[x + y * virtualConsoleSize.x] = c;
}

void Console::SetCharacterAndUpdateCursor(char c)
{
    SetCharacterAt(cursorPosition.x++, cursorPosition.y, c);

    if (cursorPosition.x >= virtualConsoleSize.x)
    {
        cursorPosition.x = 0;
        cursorPosition.y++;
    }
    if (cursorPosition.y >= virtualConsoleSize.y)
    {
        cursorPosition.x = 0;
        //  TODO : Maybe add vertical scroll?
        cursorPosition.y = 0;
    }
}

void Console::Print(const char *text)
{
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        SetCharacterAndUpdateCursor(text[i]);
    }
}

void Console::SetColor(int x, int y, int z)
{
    color.x = x;
    color.y = y;
    color.z = z;
}

const Point3dInt Console::GetColor()
{
    return color;
}
