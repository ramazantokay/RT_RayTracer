#include "Triangle.h"

Triangle::Triangle(Scene *scene, int ind_1, int ind_2, int ind_3, int mat_id)
    : m_scene(scene), v1(ind_1), v2(ind_2), v3(ind_3), material_id(mat_id)
{
    const Vec3f &v_1 = m_scene->vertex_data[ind_1];
    const Vec3f &v_2 = m_scene->vertex_data[ind_2];
    const Vec3f &v_3 = m_scene->vertex_data[ind_3];

    normal = unit_vector(cross((v_2 - v_1), (v_3 - v_1)));
}

bool Triangle::hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const
{
    rec.t = infinity;
    rec.shape = NULL;

    const Vec3f &v_1 = m_scene->vertex_data[v1];
    const Vec3f &v_2 = m_scene->vertex_data[v2];
    const Vec3f &v_3 = m_scene->vertex_data[v3];

    const Vec3f m_col1 = v_1 - v_2;
    const Vec3f m_col2 = v_1 - v_3;
    const Vec3f m_col3 = ray.direction();

    const float detA = det(m_col1, m_col2, m_col3);
    if (detA == 0.0f)
    {
        return false;
    }

    const Vec3f b = (v_1 - ray.origin()) / detA;
    
    const float beta = det(b, m_col2, m_col3);

    if (beta < 0.0f - t_min || beta > 1.0f + t_min)
    {
        return false;
    }

    const float gamma = det(m_col1, b, m_col3);

    if (gamma < 0.0f - t_min || beta + gamma > 1.0f + t_min)
    {
        return false;
    }

    const float time = det(m_col1, m_col2, b);
    
    if (time > -t_min)
    {
        rec.t = time;
        rec.shape = this;
        rec.normal = this->normal;
    }

    return true;
}

int Triangle::get_material_id() const
{
    return material_id;
}
