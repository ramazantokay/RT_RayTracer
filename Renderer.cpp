#include "Renderer.h"

Renderer::Renderer(Scene *scene) : m_scene(scene)
{
}

Vec3f Renderer::ray_color(const Ray &ray, int depth)
{
    Vec3f color;
    // std::cout << "RAY: " << ray.origin() << " " << ray.direction() << std::endl;
    HitRecord hit_record;
    hit_record.t = infinity;
    hit_record.shape = NULL;

    // MESH INTERSECTION
    for (const Mesh &mesh : m_scene->meshes)
    {
        for (const Triangle &triangle : mesh.triangles)
        {
            HitRecord temp_hr_tri;
            if (triangle.hit(ray, 0.000001, infinity, temp_hr_tri))
            {
                if (temp_hr_tri.t < hit_record.t - 0.000001 && temp_hr_tri.t > 0.0f)
                {
                    hit_record = temp_hr_tri;
                    /* code */
                }
            }
        }
    }

    // TRIANGLE INTERSECTION
    for (const Triangle &triangle : m_scene->triangles)
    {
        HitRecord temp_hr_tri;
        if (triangle.hit(ray, 0.000001, infinity, temp_hr_tri))
        {
            if (temp_hr_tri.t < hit_record.t - 0.000001 && temp_hr_tri.t > 0.0f)
            {
                hit_record = temp_hr_tri;
            }
        }
    }

    // SPHERE INTERSECTION
    for (const Sphere &sphere : m_scene->spheres)
    {
        HitRecord temp_hr;
        if (sphere.hit(ray, 0.000001, infinity, temp_hr))
        {
            // std::cout << "HITTTTTTTT"<<std::endl;
            if (temp_hr.t < hit_record.t - 0.000001 && temp_hr.t > 0.0f)
            {
                hit_record = temp_hr;
            }
        }
    }

    if (hit_record.shape == NULL)
    {
        if (m_scene->max_recursion_depth == depth)
        {
            return m_scene->background_color;
        }
        return color;
    }

    Vec3f intersection = ray.at(hit_record.t);
    Material &material = m_scene->materials[hit_record.shape->get_material_id()];
    color += material.ambient * m_scene->ambient_light;
    Vec3f w_0 = unit_vector(ray.origin() - intersection); // ray direction

    // SHADOW
    for (const PointLight &point_light : m_scene->point_lights)
    {
        bool shadow_flag = false;
        const Vec3f light_dist_vec = point_light.position - intersection;
        const Vec3f w_i = unit_vector(light_dist_vec);
        float light_dist = light_dist_vec.length();

        Ray shadow_ray(intersection + (m_scene->shadow_ray_epsilon * w_i), w_i);

        for (const Mesh &mesh : m_scene->meshes)
        {
            for (const Triangle &triangle : mesh.triangles)
            {
                HitRecord hit_record_mesh_shadow;
                if (triangle.hit(shadow_ray, 0.000001, infinity, hit_record_mesh_shadow))
                {
                    if (hit_record_mesh_shadow.t < (light_dist - m_scene->shadow_ray_epsilon) && hit_record_mesh_shadow.t > 0.0f)
                    {
                        shadow_flag = true;
                        break;
                    }
                }

                if (shadow_flag)
                    break;
            }
        }

        if (!shadow_flag)
        {
            for (const Triangle &triangle : m_scene->triangles)
            {
                HitRecord hit_record_triangle_shadow;
                if (triangle.hit(shadow_ray, 0.000001, infinity, hit_record_triangle_shadow))
                {
                    if (hit_record_triangle_shadow.t < (light_dist - m_scene->shadow_ray_epsilon) && hit_record_triangle_shadow.t > 0.0f)
                    {
                        shadow_flag = true;
                        break;
                    }
                }
            }
        }

        if (!shadow_flag)
        {
            for (const Sphere &sphere : m_scene->spheres)
            {
                HitRecord shadow_hit_record;
                if (sphere.hit(shadow_ray, 0.000001, infinity, shadow_hit_record))
                {
                    if (shadow_hit_record.t < (light_dist - m_scene->shadow_ray_epsilon) && shadow_hit_record.t > 0.0f)
                    {
                        shadow_flag = true;
                        break;
                    }
                }
            }
        }

        if (!shadow_flag)
        {
            float light_dist_sqrt = light_dist * light_dist;

            float d_cos_theta = dot(hit_record.normal, w_i);
            color += (material.diffuse * point_light.intensity) * d_cos_theta / light_dist_sqrt;

            float s_cos_theta = fmax(0.0f, dot(hit_record.normal, unit_vector(w_0 + w_i)));
            color += (material.specular * point_light.intensity) * pow(s_cos_theta, material.phong_exponent) / light_dist_sqrt;
        }
    }

    // MIRROR
    if (material.mirror != Vec3f(0.0f) && depth > 0)
    {
        Vec3f w_r = unit_vector(2 * (dot(hit_record.normal, w_0) * hit_record.normal) - w_0);
        Ray reflect_ray(intersection + (w_r * m_scene->shadow_ray_epsilon), w_r);
        color += material.mirror * ray_color(reflect_ray, depth - 1);
    }

    return color;
}

void Renderer::render(int camera_index, Vec3f *pixels, const int row, const int height)
{
    Camera &camera = m_scene->cameras[camera_index];
    Image &image = camera.image;
    int t_width = image.width;
    int t_height = image.height;

    for (int j = row; j < t_height; j += height)
    {
        for (int i = 0; i < t_width; i++)
        {
            Vec3f color = ray_color(camera.get_ray(i, j), m_scene->max_recursion_depth);
            pixels[j * t_width + i] = Vec3f(std::min(255, std::max(0, int(color.x))), std::min(255, std::max(0, int(color.y))), std::min(255, std::max(0, int(color.z))));
        }
    }
}