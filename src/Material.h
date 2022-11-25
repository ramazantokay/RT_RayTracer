#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vec3f.h"

class Material
{
public:
    Vec3f ambient;
    Vec3f diffuse;
    Vec3f specular;
    Vec3f mirror;
    float phong_exponent;
    bool is_mirror;
};

#endif
