#include <SDL2/SDL.h>

#include "core/graphics/textures/TextureManager.h"
#include "utils/Log.h"
#include "core/exceptions/ResourceLoadException.h"

TextureManager *TextureManager::instance = 0;

void TextureManager::Init(SDL_Renderer *renderer)
{
    Log::GetInstance()->Info("TextureManager::Init", "TextureManager Initializing");
    this->renderer = renderer;
}

void TextureManager::Clean()
{
    Log::GetInstance()->Info("TextureManager::Clean", "TextureManager Shutting Down");

    for (auto &[name, pointer] : textures)
    {
        Log::GetInstance()->Info("TextureManager::Cleanup", "Deleting texture: %s", name.c_str());
        SDL_DestroyTexture(pointer);
    }
    textures.clear();
}

SDL_Texture *TextureManager::Add(const char *fileName)
{
    //  Check if resource already was loaded
    if (textures.count(fileName) != 0)
    {
        return textures[fileName];
    }

    // Load image at specified path
    SDL_Surface *tmp = IMG_Load(fileName);
    if (!tmp)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        char *buffer = new char[512];
        sprintf(buffer, "Unable to load image: %s. SDL Error: %s", fileName, IMG_GetError());

        Log::GetInstance()->Error("Image::Load", buffer);
        throw ResourceLoadException(buffer);
    }

    // Convert surface to screen format
    SDL_Texture *image = SDL_CreateTextureFromSurface(renderer, tmp);
    if (image == NULL)
    {
        char *buffer = new char[512];
        sprintf(buffer, "Unable to create texture from image: %s. SDL Error: %s", fileName, IMG_GetError());
        Log::GetInstance()->Error("Image::Load", buffer);
        throw ResourceLoadException(buffer);
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(tmp);

    textures[fileName] = image;

    return image;
}
