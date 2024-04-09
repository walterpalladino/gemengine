#pragma once

#include <nlohmann/json.hpp>

#include "core/graphics/sprites/Sprite.h"

using json = nlohmann::json;

class SpriteParser
{
public:
    static Sprite *JSONParse(json data);
};
