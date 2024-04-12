#include "core/sound/SoundParser.h"
#include "core/sound/SoundManager.h"

#include "core/config/Config.h"

Sound *SoundParser::JSONParse(json data)
{
    string name = data["name"];
    string src = data["src"];
    string sampleFileName = Config::Instance()->config_data.resource_folder + "/" + src;

    Mix_Chunk *chunk = SoundManager::Instance()->AddSound(sampleFileName);

    Sound *sound = new Sound(name, chunk);

    return sound;
}