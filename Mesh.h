#ifndef MESH_H
#define MESH_H

#include <vector>

#include "Triangle.h"

class Triangle;

class Mesh
{
public:
    int material_id;
    int texture_id;
    std::vector<Triangle> triangles;
};

#endif