#include "Scene.h"
#include "ext/tinyxml2.h"
#include <cmath>
#include <sstream>
#include <stdexcept>

// PARSING

Scene::Scene(const std::string &scene_name)
{
    tinyxml2::XMLDocument file;
    std::stringstream stream;
    // std::cout << "Sceneee:  " << scene_name << std::endl;
    auto res = file.LoadFile(scene_name.c_str());
    if (res)
    {
        // std::cout << "HOOPPPPP:  "<< std::endl;
        throw std::runtime_error("Error: The xml file cannot be loaded.");
    }

    auto root = file.FirstChild();
    if (!root)
    {
        throw std::runtime_error("Error: Root is not found.");
    }

    // Get BackgroundColor
    auto element = root->FirstChildElement("BackgroundColor");
    if (element)
    {
        stream << element->GetText() << std::endl;
    }
    else
    {
        stream << "0 0 0" << std::endl;
    }
    stream >> background_color.x >> background_color.y >> background_color.z;

    // Get ShadowRayEpsilon
    element = root->FirstChildElement("ShadowRayEpsilon");
    if (element)
    {
        stream << element->GetText() << std::endl;
    }
    else
    {
        stream << "0.001" << std::endl;
    }
    stream >> shadow_ray_epsilon;

    // Get MaxRecursionDepth
    element = root->FirstChildElement("MaxRecursionDepth");
    if (element)
    {
        stream << element->GetText() << std::endl;
    }
    else
    {
        stream << "0" << std::endl;
    }
    stream >> max_recursion_depth;

    // Get Cameras
    element = root->FirstChildElement("Cameras");
    element = element->FirstChildElement("Camera");
    while (element)
    {
        auto child = element->FirstChildElement("Position");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Gaze");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Up");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("NearPlane");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("NearDistance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("ImageResolution");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("ImageName");
        stream << child->GetText() << std::endl;

        Vec3f position, up, gaze;
        float near_plane_t, near_plane_r, near_plane_b, near_plane_l;
        float near_distance;
        int image_width, image_height;
        std::string image_name;

        stream >> position.x >> position.y >> position.z;
        stream >> gaze.x >> gaze.y >> gaze.z;
        stream >> up.x >> up.y >> up.z;
        stream >> near_plane_l >> near_plane_r >> near_plane_b >> near_plane_t;
        stream >> near_distance;
        stream >> image_width >> image_height;
        stream >> image_name;

        // std::cout << "HOOPPPPP:  "<< image_name << std::endl;

        Camera camera(up, gaze, position, near_plane_t, near_plane_r, near_plane_b, near_plane_l, near_distance, image_width, image_height, image_name);

        cameras.push_back(camera);

        element = element->NextSiblingElement("Camera");
    }

    // Get Lights
    element = root->FirstChildElement("Lights");
    auto child = element->FirstChildElement("AmbientLight");
    stream << child->GetText() << std::endl;
    stream >> ambient_light.x >> ambient_light.y >> ambient_light.z;
    element = element->FirstChildElement("PointLight");
    PointLight point_light;
    while (element)
    {
        child = element->FirstChildElement("Position");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Intensity");
        stream << child->GetText() << std::endl;

        stream >> point_light.position.x >> point_light.position.y >> point_light.position.z;
        stream >> point_light.intensity.x >> point_light.intensity.y >> point_light.intensity.z;

        point_lights.push_back(point_light);
        element = element->NextSiblingElement("PointLight");
    }

    // Get Materials
    element = root->FirstChildElement("Materials");
    element = element->FirstChildElement("Material");
    Material material;
    while (element)
    {
        material.is_mirror = (element->Attribute("type", "mirror") != NULL);

        child = element->FirstChildElement("AmbientReflectance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("DiffuseReflectance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("SpecularReflectance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("MirrorReflectance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("PhongExponent");
        stream << child->GetText() << std::endl;

        stream >> material.ambient.x >> material.ambient.y >> material.ambient.z;
        stream >> material.diffuse.x >> material.diffuse.y >> material.diffuse.z;
        stream >> material.specular.x >> material.specular.y >> material.specular.z;
        stream >> material.mirror.x >> material.mirror.y >> material.mirror.z;
        stream >> material.phong_exponent;

        materials.push_back(material);
        element = element->NextSiblingElement("Material");
    }

    // Get VertexData
    element = root->FirstChildElement("VertexData");
    stream << element->GetText() << std::endl;
    Vec3f vertex;
    while (!(stream >> vertex.x).eof())
    {
        stream >> vertex.y >> vertex.z;
        vertex_data.push_back(vertex);
    }
    stream.clear();

    // Get Meshes
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("Mesh");
    Mesh mesh;
    while (element)
    {
        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;
        stream >> mesh.material_id;
        mesh.material_id--;

        child = element->FirstChildElement("Faces");
        stream << child->GetText() << std::endl;
        // Face face;
        int v0_id, v1_id, v2_id;

        while (!(stream >> v0_id).eof())
        {
            stream >> v1_id >> v2_id;
            mesh.triangles.push_back(Triangle(this, v0_id - 1, v1_id - 1, v2_id - 1, mesh.material_id));
            // mesh.faces.push_back(face);
        }
        stream.clear();

        meshes.push_back(std::move(mesh));
        mesh.triangles.clear();
        element = element->NextSiblingElement("Mesh");
    }
    stream.clear();

    // Get Triangles
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("Triangle");
    // Triangle triangle;
    while (element)
    {
        int material_id;
        int v0_id, v1_id, v2_id;

        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;
        stream >> material_id;
        material_id--;

        child = element->FirstChildElement("Indices");
        stream << child->GetText() << std::endl;
        stream >> v0_id >> v1_id >> v2_id;

        triangles.push_back(Triangle(this, v0_id - 1, v1_id - 1, v2_id - 1, material_id));
        element = element->NextSiblingElement("Triangle");
    }

    // Get Spheres
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("Sphere");
    // Sphere sphere;
    while (element)
    {
        int material_id, center;
        float radius;

        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;
        stream >> material_id;
        material_id--;

        child = element->FirstChildElement("Center");
        stream << child->GetText() << std::endl;
        stream >> center;
        const Vec3f &center_sphere = vertex_data[center - 1];

        child = element->FirstChildElement("Radius");
        stream << child->GetText() << std::endl;
        stream >> radius;

        spheres.push_back(Sphere(center_sphere, radius, material_id));
        element = element->NextSiblingElement("Sphere");
    }
}
