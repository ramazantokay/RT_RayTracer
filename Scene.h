#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vec3f.h"

class Scene
{
public:
    Scene(const std::string &scene_name);

public:
    // Data
    Vec3f background_color;
    float shadow_ray_epsilon;
    int max_recursion_depth;
    Vec3f ambient_light;

    std::vector<Camera> cameras;
    std::vector<PointLight> point_lights;
    std::vector<Material> materials;
    std::vector<Vec3f> vertex_data;
    std::vector<Mesh> meshes;
    std::vector<Triangle> triangles;
    std::vector<Sphere> spheres;
};

#endif