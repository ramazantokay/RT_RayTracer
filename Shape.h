#ifndef SHAPE_H
#define SHAPE_H

#include "HitRecord.h"
#include "Ray.h"

class Shape
{
public:
    virtual int get_material_id() const = 0;
    virtual bool hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const = 0;
};

#endif