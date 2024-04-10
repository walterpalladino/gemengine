#pragma once

#include <nlohmann/json.hpp>

#include "core/sound/Track.h"

using json = nlohmann::json;

class TrackParser
{
public:
    static Track *JSONParse(json data);
};