#pragma once

#include <nlohmann/json.hpp>

#include "core/gemobject/GemObject.h"

using json = nlohmann::json;

class GemObjectParser
{
public:
    static GemObject *JSONParse(json data);
};