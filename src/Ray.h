#ifndef RAY_H
#define RAY_H

#include "Vec3f.h"

class Ray
{

public:
    Ray() {}
    Ray(const Vec3f &origin, const Vec3f &direction) : orig(origin), direct(direction), t(0.0f) {}
    Ray(const Vec3f &origin, const Vec3f &direction, float t_val) : orig(origin), direct(direction), t(t_val) {}

    Vec3f at(float t) const
    {
        return orig + (t * direct);
    }

    Vec3f origin() const { return orig; }
    Vec3f direction() const { return direct; }
    float time() const { return t; }

public:
    Vec3f orig;
    Vec3f direct;
    float t;
};

#endif
