#include "vector.h"

Vector::Vector()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector Vector::Cross(Vector v)
{
    return Vector(
                y * v.z - z * v.y,
                x * v.z - z * v.x,
                x * v.y - y * v.x
                );
}
