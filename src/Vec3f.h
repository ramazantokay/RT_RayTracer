#ifndef VEC3F_H
#define VEC3F_H

#include <iostream>
#include <cmath>

using std::sqrt;

class Vec3f
{
public:
    Vec3f() : x(0.0f), y(0.0f), z(0.0f) {}
    Vec3f(const Vec3f &v) : x(v.x), y(v.y), z(v.z) {}
    Vec3f(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
    Vec3f(float val) : x(val), y(val), z(val) {}

    Vec3f operator-() const { return Vec3f(-x, -y, -z); }

    Vec3f &operator+=(const Vec3f &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3f &operator-=(const Vec3f &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vec3f &operator*=(const Vec3f &v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    Vec3f &operator/=(const Vec3f &v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    Vec3f &operator+=(const float value)
    {
        x += value;
        y += value;
        z += value;
        return *this;
    }

    Vec3f &operator-=(const float value)
    {
        x -= value;
        y -= value;
        z -= value;
        return *this;
    }

    Vec3f &operator*=(const float value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    Vec3f &operator/=(const float value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    inline bool operator==(const Vec3f& v) const
    {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }
    
    inline bool operator!=(const Vec3f &v) const
    {
        return !(*this == v);
    }

    float lenght_squared() const
    {
        return x * x + y * y + z * z;
    }

    float length() const
    {
        return sqrt(lenght_squared());
    }

public:
    float x, y, z;
};

// aliases
using color = Vec3f; // RGB color

// Vec3f Utility Functions
// @TODO: will implement variation of operator overloading

inline Vec3f operator+(const Vec3f &u, const Vec3f &v)
{
    return Vec3f(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vec3f operator-(const Vec3f &u, const Vec3f &v)
{
    return Vec3f(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vec3f operator*(const Vec3f &u, const Vec3f &v)
{
    return Vec3f(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vec3f operator/(const Vec3f &u, const Vec3f &v)
{
    return Vec3f(u.x / v.x, u.y / v.y, u.z / v.z);
}

inline Vec3f operator*(float val, const Vec3f &v)
{
    return Vec3f(val * v.x, val * v.y, val * v.z);
}

inline Vec3f operator*(Vec3f &v, float val)
{
    return val * v;
}

inline Vec3f operator/(Vec3f v, float val)
{
    return (1 / val) * v;
}

inline float dot(const Vec3f &u, const Vec3f &v)
{
    return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

inline Vec3f cross(const Vec3f &u, const Vec3f &v)
{
    return Vec3f(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x);
}

inline Vec3f unit_vector(Vec3f v)
{
    return v / v.length();
}

inline std::ostream &operator<<(std::ostream &out, const Vec3f &v)
{
    return out << v.x << " " << v.y << " " << v.z;
}


#endif
