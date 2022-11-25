#include <iostream>
#include <thread>

#include "ext/TimeDiff.h"
#include "ext/ppm.h"
#include "Renderer.h"
#include "Scene.h"
#include "Vec3f.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Scene file pleaseeeee!" << std::endl;
        return 1;
    }

    Scene scene(argv[1]);
    std::cout << "Scene OK!" << std::endl;
    
    Renderer renderer(&scene);
    std::cout << "Renderer OK!" << std::endl;

    const int numThreads = std::max(1, static_cast<int>(std::thread::hardware_concurrency()));
    std::cout << "RT will be using: " << numThreads << " threads" << std::endl;

    int camera_count = scene.cameras.size();

    for (int i = 0; i < camera_count; i++)
    {
        const Image &image = scene.cameras[i].image;
        const int width = image.width;
        const int height = image.height;

        Vec3f *pixels = new Vec3f[width * height];

        auto start_time = std::chrono::system_clock::now();

        std::vector<std::thread> threads;
        for (int t = 0; t < numThreads; t++)
        {
            threads.emplace_back(std::thread(&Renderer::render, &renderer, i, pixels, t, numThreads));
        }

        for (auto &thread : threads)
        {
            thread.join();
        }

        auto end_time = std::chrono::system_clock::now();

        unsigned char *image_arr = new unsigned char[width * height * 3];

        int idx = 0;
        for (int j = 0; j < height; j++)
        {
            for (int i_2 = 0; i_2 < width; i_2++)
            {
                Vec3f &pixel = pixels[j * width + i_2];
                image_arr[idx++] = pixel.x;
                image_arr[idx++] = pixel.y;
                image_arr[idx++] = pixel.z;
            }
        }

        delete[] pixels;

        write_ppm(("my_out/" + image.image_name).c_str(), image_arr, width, height);

        delete[] image_arr;

        std::cout << "my_out/" + image.image_name << " is saved" << std::endl;
        print_time_diff(std::cout, start_time, end_time);
        std::cout << std::endl;
    }

    return 0;
}
