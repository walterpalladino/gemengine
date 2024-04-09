#include "core/graphics/parallax/ParallaxParser.h"
#include "core/graphics/textures/TextureManager.h"
#include "core/config/Config.h"

Parallax *ParallaxParser::JSONParse(json data)
{
    Parallax *parallax = new Parallax();

    string src = data.at("src");
    string src_file = Config::Instance()->config_data.resource_folder + "/" + src;

    SDL_Texture *texture = TextureManager::Instance()->Add(src_file.c_str());
    parallax->SetTexture(texture);

    return parallax;
}