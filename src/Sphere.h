#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>

#include "Common.h"
#include "Shape.h"

class Sphere : public Shape
{
public:
    Sphere(const Vec3f &c, float r, int m_id) : center(c), radius(r), material_id(m_id) {}

    int get_material_id() const override;
    bool hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const override;

public:
    Vec3f center;
    float radius;
    int material_id;
};

#endif
