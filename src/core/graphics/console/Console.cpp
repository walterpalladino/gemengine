#include <iostream>
#include <string>

#include "core/graphics/console/Console.h"
#include "core/graphics/textures/TextureManager.h"
#include "core/graphics/text/FontsManager.h"

#include "utils/Log.h"
#include "core/config/Config.h"
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

        Log::Instance()->Info("Console::Init", "Console initialized");
    }
}

void Console::Init(SDL_Renderer *renderer, int x, int y, int width, int height, const char *fileName, const int fontSize)
{
    Log::Instance()->Info("Console::Init", "Initializing");

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
    Log::Instance()->Info("Console::LoadFont", "Loading font : %s", fileName);
    fontTexture = TextureManager::Instance()->Add(fileName);
    //  Get texture information
    SDL_QueryTexture(fontTexture, NULL, NULL, &textureRect.w, &textureRect.h);
}

void Console::Cleanup()
{
    Log::Instance()->Info("Console::Cleanup", "Cleanup");

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

char Console::GetCharacterAt(int x, int y)
{
    if (x >= 0 && x < virtualConsoleSize.x && y >= 0 && y < virtualConsoleSize.y)
    {
        return consoleBuffer[x + y * virtualConsoleSize.x];
    }
    return ' '; //  Default character
}

void Console::Shift(int direction, bool rollContent = false)
{
    if (direction != 1 && direction != 2 && direction != 3 && direction != 4 && direction != 6 && direction != 8 && direction != 12 && direction != 9)
    {
        return;
    }

    //  UP && DOWN
    if (direction & CONSOLE_SHIFT_UP)
    {
        char *buffer = new char[virtualConsoleSize.x];
        for (int x = 0; x < virtualConsoleSize.x; x++)
        {
            if (rollContent)
                buffer[x] = GetCharacterAt(x, 0);
            else
                buffer[x] = ' ';
        }
        for (int y = 1; y < virtualConsoleSize.y; y++)
        {
            for (int x = 0; x < virtualConsoleSize.x; x++)
            {
                SetCharacterAt(x, y - 1, GetCharacterAt(x, y));
            }
        }
        for (int x = 0; x < virtualConsoleSize.x; x++)
        {
            SetCharacterAt(x, virtualConsoleSize.y - 1, buffer[x]);
        }
        delete[] buffer;
    }
    else if (direction & CONSOLE_SHIFT_DOWN)
    {
        char *buffer = new char[virtualConsoleSize.x];
        for (int x = 0; x < virtualConsoleSize.x; x++)
        {
            if (rollContent)
                buffer[x] = GetCharacterAt(x, virtualConsoleSize.y - 1);
            else
                buffer[x] = ' ';
        }
        for (int y = virtualConsoleSize.y - 2; y >= 0; y--)
        {
            for (int x = 0; x < virtualConsoleSize.x; x++)
            {
                SetCharacterAt(x, y + 1, GetCharacterAt(x, y));
            }
        }
        for (int x = 0; x < virtualConsoleSize.x; x++)
        {
            SetCharacterAt(x, 0, buffer[x]);
        }
        delete[] buffer;
    }

    //  LEFT && RIGHT
    if (direction & CONSOLE_SHIFT_LEFT)
    {
        char *buffer = new char[virtualConsoleSize.y];
        for (int y = 0; y < virtualConsoleSize.y; y++)
        {
            if (rollContent)
                buffer[y] = GetCharacterAt(0, y);
            else
                buffer[y] = ' ';
        }
        for (int x = 1; x < virtualConsoleSize.x; x++)
        {
            for (int y = 0; y < virtualConsoleSize.y; y++)
            {
                SetCharacterAt(x - 1, y, GetCharacterAt(x, y));
            }
        }
        for (int y = 0; y < virtualConsoleSize.y; y++)
        {
            SetCharacterAt(virtualConsoleSize.x - 1, y, buffer[y]);
        }
        delete[] buffer;
    }
    else if (direction & CONSOLE_SHIFT_RIGHT)
    {
        char *buffer = new char[virtualConsoleSize.y];
        for (int y = 0; y < virtualConsoleSize.y; y++)
        {
            if (rollContent)
                buffer[y] = GetCharacterAt(virtualConsoleSize.x - 1, y);
            else
                buffer[y] = ' ';
        }
        for (int x = virtualConsoleSize.x - 2; x >= 0; x--)
        {
            for (int y = 0; y < virtualConsoleSize.y; y++)
            {
                SetCharacterAt(x + 1, y, GetCharacterAt(x, y));
            }
        }
        for (int y = 0; y < virtualConsoleSize.y; y++)
        {
            SetCharacterAt(0, y, buffer[y]);
        }
        delete[] buffer;
    }
}

void Console::SetBuffer(const char *text)
{
    int len = strlen(text);
    if (len > virtualConsoleSize.x * virtualConsoleSize.y)
    {
        len = virtualConsoleSize.x * virtualConsoleSize.y;
    }
    for (int i = 0; i < len; i++)
    {
        consoleBuffer[i] = text[i];
    }
}