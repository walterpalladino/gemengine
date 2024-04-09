#pragma once

#include <nlohmann/json.hpp>

#include "core/graphics/text/Text.h"

using json = nlohmann::json;

class TextParser
{
public:
    static Text *JSONParse(json data);
};
