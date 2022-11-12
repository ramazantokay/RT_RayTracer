#ifndef RENDERER_H
#define RENDERER_H

#include "Common.h"
#include "Scene.h"

class Scene;

class Renderer
{
public:
    Renderer(Scene *scene);
    
    Vec3f ray_color(const Ray &ray, int depth);
    void render(int camera_index, Vec3f *pixels, const int row, const int height = 1);

public:
    Scene *m_scene;
};

#endif
