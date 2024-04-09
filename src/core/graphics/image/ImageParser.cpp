#include "core/graphics/image/ImageParser.h"
#include "core/graphics/textures/TextureManager.h"
#include "core/config/Config.h"

Image *ImageParser::JSONParse(json data)
{
    Image *image = new Image();

    string src = data.at("src");
    string src_file = Config::Instance()->config_data.resource_folder + "/" + src;

    SDL_Texture *texture = TextureManager::Instance()->Add(src_file.c_str());
    image->SetTexture(texture);

    return image;
}