#include "Sphere.h"

bool Sphere::hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const
{
    Vec3f oc = ray.origin() - center;
    float a = ray.direction().lenght_squared();
    float h_b = dot(oc, ray.direction());
    float c = oc.lenght_squared() - radius * radius;

    float discriminant = h_b * h_b - a * c;
    if (discriminant < 0)
    {
        rec.t = infinity;
        rec.shape = NULL;
        return false;
    }

    float sqrt_discriminant = sqrt(discriminant);
    float root = (-h_b - sqrt_discriminant) / a;
    if (root < t_min || t_max < root)
    {
        root = (-h_b + sqrt_discriminant) / a;
        if (root < t_min || t_max < root)
        {
            rec.t = infinity;
            rec.shape = NULL;
            return false;
        }
    }
    rec.t = root;
    rec.normal = (ray.at(rec.t) - center) / radius;
    rec.shape = this;

    return true;
}

int Sphere::get_material_id() const
{
    return material_id;
}