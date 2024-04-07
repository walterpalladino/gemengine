
#include "math/Vector3d.h"

struct Transform
{
    Vector3d position = Vector3d::Zero();
    Vector3d rotation = Vector3d::Zero();
    Vector3d scale = Vector3d::One();
};