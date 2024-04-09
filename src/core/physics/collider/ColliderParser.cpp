
#include "core/physics/collider/ColliderParser.h"

Collider *ColliderParser::JSONParse(json data)
{
    Collider *collider = new Collider();

    collider->enabled = data.at("enabled");
    collider->offset = Vector3d(data.at("offset").at("x"), data.at("offset").at("y"), data.at("offset").at("z"));
    collider->size = Vector3d(data.at("size").at("x"), data.at("size").at("y"), data.at("size").at("z"));
    collider->mask = data.at("mask");

    return collider;
}