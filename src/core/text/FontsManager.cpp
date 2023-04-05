
#include <SDL2_ttf/SDL_ttf.h>

#include "core/text/FontsManager.h"
#include "utils/Log.h"
#include "exceptions/ResourceLoadException.h"

FontsManager *FontsManager::instance = 0;

void FontsManager::Init()
{
    Log::GetInstance()->Info("FontsManager::Init", "FontsManager Initializing");
    // fonts.reserve(MAX_FONTS_PER_APP);
    TTF_Init();
}

void FontsManager::Clean()
{
    Log::GetInstance()->Info("FontsManager::Clean", "FontsManager Shutting Down");

    for (auto &[fontName, fontPointer] : fonts)
    {
        Log::GetInstance()->Info("FontsManager::Cleanup", "Deleting font: %s", fontName.c_str());
        TTF_CloseFont(fontPointer);
    }
    fonts.clear();

    TTF_Quit();
}

string FontsManager::AddFont(string fontFileName, int size)
{
    Log::GetInstance()->Info("FontsManager::AddFont", "Adding font %s size %i", fontFileName.c_str(), size);

    string key = GetKey(fontFileName, size);
    if (fonts.count(key) != 0)
    {
        return key;
    }
    TTF_Font *font = TTF_OpenFont(fontFileName.c_str(), size);

    if (font == NULL)
    {
        char *buffer = new char[512];
        sprintf(buffer, "Unable to load font: %s. TTF Error: %s", fontFileName.c_str(), TTF_GetError());

        Log::GetInstance()->Error("FontsManager::AddFont", buffer);
        throw ResourceLoadException(buffer);
    }

    fonts[key] = font;
    return key;
}

string FontsManager::GetKey(string fontFileName, int size)
{
    char *buffer = new char[512];
    sprintf(buffer, "%s::%i", fontFileName.c_str(), size);

    return string(buffer);
}
