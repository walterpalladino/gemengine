#pragma once

#include <nlohmann/json.hpp>

#include "core/graphics/parallax/Parallax.h"

using json = nlohmann::json;

class ParallaxParser
{
public:
    static Parallax *JSONParse(json data);
};
