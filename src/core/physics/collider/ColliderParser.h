#pragma once

#include <nlohmann/json.hpp>

#include "core/physics/collider/Collider.h"

using json = nlohmann::json;

class ColliderParser
{

public:
    static Collider *JSONParse(json data);
};