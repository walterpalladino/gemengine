#include "core/graphics/text/TextParser.h"

#include "core/config/Config.h"

Text *TextParser::JSONParse(json data)
{
    Text *text = new Text();

    string src = data.at("src");
    string src_file = Config::Instance()->config_data.resource_folder + "/" + src;

    text->Init("SDL2 text", src_file.c_str(), 24);

    return text;
}
