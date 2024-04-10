#include "core/sound/TrackParser.h"
#include "core/sound/SoundManager.h"

#include "core/config/Config.h"

Track *TrackParser::JSONParse(json data)
{
    Track *track = new Track();

    string name = data["name"];
    string src = data["src"];
    string sampleFileName = Config::Instance()->config_data.resource_folder + "/" + src;

    SoundManager::Instance()->AddTrack(name, sampleFileName);

    track->SetName(name);

    return track;
}