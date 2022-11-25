#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Common.h"
#include "Scene.h"
#include "Shape.h"

class Scene;

class Triangle : public Shape
{
public:
    Triangle(Scene *scene, int ind_1, int ind_2, int ind_3, int mat_id);

    inline float det(const Vec3f &vec1, const Vec3f &vec2, const Vec3f &vec3) const
    {
        return vec1.x * (vec2.y * vec3.z - vec3.y * vec2.z) +
               vec2.x * (vec3.y * vec1.z - vec1.y * vec3.z) +
               vec3.x * (vec1.y * vec2.z - vec2.y * vec1.z);
    }

    bool hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const override;
    int get_material_id() const override;

public:
    Scene *m_scene;
    int v1, v2, v3;
    Vec3f normal;
    int material_id;
};

#endif
