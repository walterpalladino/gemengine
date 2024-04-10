#include "core/sound/SoundParser.h"
#include "core/sound/SoundManager.h"

#include "core/config/Config.h"

Sound *SoundParser::JSONParse(json data)
{
    Sound *sound = new Sound();

    string name = data["name"];
    string src = data["src"];
    string sampleFileName = Config::Instance()->config_data.resource_folder + "/" + src;

    SoundManager::Instance()->AddSound(name, sampleFileName);

    sound->SetName(name);

    return sound;
}