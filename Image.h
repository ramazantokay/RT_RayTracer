#ifndef IMAGE_H
#define IMAGE_H

#include "Common.h"

class Image
{
public:
    Image(float t, float r, float b, float l, float dist, int img_w, int img_h, std::string img_name)
        : top(t), right(r), bottom(b), left(l), distance(dist), width(img_w), height(img_h), image_name(img_name) {}

public:
    float top, right, bottom, left;
    float distance;
    int width, height;
    std::string image_name;
};

#endif