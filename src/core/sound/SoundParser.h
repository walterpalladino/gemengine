#pragma once

#include <nlohmann/json.hpp>

#include "core/sound/Sound.h"

using json = nlohmann::json;

class SoundParser
{
public:
    static Sound *JSONParse(json data);
};