#include "core/sound/TrackParser.h"
#include "core/sound/SoundManager.h"

#include "core/config/Config.h"

Track *TrackParser::JSONParse(json data)
{
    string name = data["name"];
    string src = data["src"];
    string sampleFileName = Config::Instance()->config_data.resource_folder + "/" + src;

    Mix_Music *music = SoundManager::Instance()->AddTrack(sampleFileName);

    Track *track = new Track(name, music);

    return track;
}