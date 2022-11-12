#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"
#include "Image.h"

class Camera
{
public:
    Camera(const Vec3f &up, const Vec3f &gaze, const Vec3f &pos, float t, float r, float b, float l,
           float distance, int img_width, int img_height, std::string img_name)
        : position(pos), image(t, r, b, l, distance, img_width, img_height, img_name)
    {
        w = -(unit_vector(gaze));
        u = unit_vector(cross(unit_vector(up), w));
        v = unit_vector(cross(w, u));

        top_left_corner = position - w * image.distance + image.left * u + image.top * v;
        // std::cout << "top left corner "<< top_left_corner << std::endl;
    }

    Ray get_ray(int x, int y)
    {
        float s_u = (image.right - image.left) * (x + 0.5f) / image.width;
        float s_v = (image.top - image.bottom) * (y + 0.5f) / image.height;

        Vec3f s = top_left_corner + s_u * u - s_v * v;
        return Ray(position, (s - position));
    }

public:
    Vec3f u;
    Vec3f v;
    Vec3f w;
    Vec3f position;
    Vec3f top_left_corner;
    Image image;
};

#endif