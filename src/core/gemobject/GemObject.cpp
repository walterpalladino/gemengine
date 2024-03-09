#include "GemObject.h"

void GemObject::JSONParse(json data)
{

    name = data["name"];
    enabled = data["enabled"];
    zOrder = data["z_order"];
    layer = data["layer"];

    json json_position = data.at("position");
    position = Vector3d(json_position.at("x"), json_position.at("y"), json_position.at("z"));

    json json_rotation = data.at("rotation");
    rotation = Vector3d(json_rotation.at("x"), json_rotation.at("y"), json_rotation.at("z"));

    json json_scale = data.at("scale");
    scale = Vector3d(json_scale.at("x"), json_scale.at("y"), json_scale.at("z"));
}
