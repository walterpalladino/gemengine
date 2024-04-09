#pragma once

#include <nlohmann/json.hpp>

#include "core/graphics/image/Image.h"

using json = nlohmann::json;

class ImageParser
{
public:
    static Image *JSONParse(json data);
};
