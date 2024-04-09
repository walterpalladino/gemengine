#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL2_ttf/SDL_ttf.h>

using namespace std;

#define MAX_FONTS_PER_APP 512

class FontsManager
{
public:
    static FontsManager *Instance()
    {
        if (instance == 0)
        {
            instance = new FontsManager();
        }
        return instance;
    }

    void Init();
    void Cleanup();

    TTF_Font *Add(string fontFileName, int size);

private:
    FontsManager() {}
    ~FontsManager() {}

    static FontsManager *instance;

    unordered_map<string, TTF_Font *> fonts;

    string GetKey(string fontFileName, int size);
};