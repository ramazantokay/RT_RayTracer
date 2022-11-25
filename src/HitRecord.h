#ifndef HITRECORD_H
#define HITRECORD_H

#include "Vec3f.h"

class Shape;

class HitRecord
{
public:
    Vec3f normal;
    const Shape *shape;
    float t;
};

#endif
