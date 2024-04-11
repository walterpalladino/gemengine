#pragma once

#include <nlohmann/json.hpp>

#include "core/gemobject/GemObject.h"

using json = nlohmann::json;

class GemObjectParser
{
private:
    static Transform ParseTransform(json data);

public:
    static GemObject *JSONParse(json data);
};