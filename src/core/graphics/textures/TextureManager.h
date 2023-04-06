#pragma once

#include <string>
#include <unordered_map>

#include <SDL2_image/SDL_image.h>

#define MAX_TEXTURES_PER_APP 2048

using namespace std;

class TextureManager
{

public:
    static TextureManager *Instance()
    {
        if (instance == 0)
        {
            instance = new TextureManager();
        }
        return instance;
    }

    void Init(SDL_Renderer *renderer);
    void Clean();

    SDL_Texture *Add(const char *fileName);

private:
    TextureManager() {}
    ~TextureManager() {}

    static TextureManager *instance;

    SDL_Renderer *renderer;

    unordered_map<string, SDL_Texture *> textures;
};