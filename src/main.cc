#include "Hittable/Hittable.hh"
#include "Materials/Dielectric.hh"
#include "Materials/Matte.hh"
#include "Materials/Metal.hh"
#include "Shapes/Plane.hh"
#include "Shapes/Sphere.hh"
#include "Shapes/Triangle.hh"
#include "WorldBuilding/Camera.hh"
#include "WorldBuilding/HittableList.hh"
#include "WorldBuilding/Ray.hh"
#include "WorldBuilding/Vec.hh"
#include "util.hh"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <vector>

Vec ray_color(const Ray& ray, const HittableList& world, const int depth) {
    // no light to gather at bounce limit
    if (depth <= 0)
        return Vec{};
    hit_record rec;
    if (world.hit(ray, 0.01, 1e18, rec)) {
        Ray scattered;
        Vec attenuation;

        if (rec.mat_ptr->scatter(ray, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth - 1);
        }
    }
    auto t{(ray.dir.unit_vector().v + 1.0) * 0.5};
    return Vec(1, 1, 1) * (1 - t) + Vec(0.5, 1.0, 1.0) * t;
}

int main() {
    // 16:9 ratio
    const int img_width{1920};
    const int img_height{1080};

    std::vector<Vec> img_buff(img_width * img_height);

    // camera
    const Vec lookfrom(0, 0, 5);
    const Vec lookat(0, 0, 0);
    const Vec vup(0, 1, 0);
    const double vfov{45.0};
    const double aspect_ratio{double(img_width) / img_height};

    const Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio);

    // colors
    const auto matte_red{std::make_shared<Matte>(Vec(0.7, 0.3, 0.3))};
    const auto matte_grn{std::make_shared<Matte>(Vec(0.1, 0.7, 0.5))};
    const auto matte_blu{std::make_shared<Matte>(Vec(0.2, 0.3, 0.6))};
    const auto matte_prp{std::make_shared<Matte>(Vec(0.5, 0.1, 0.9))};
    const auto metal_slv{std::make_shared<Metal>(Vec(0.8, 0.8, 0.8), 0.1)};
    const auto metal_gld{std::make_shared<Metal>(Vec(0.8, 0.6, 0.2), 0.0)};
    const auto glass{std::make_shared<Dielectric>(1.5)};

    HittableList objs{
        new Plane{Vec(0, -1, 0), Vec(0, 1, 0), matte_red},      // floor
        new Plane{Vec(0, 0.0, -5.0), Vec(0, 0, -1), matte_grn}, // back wall
        new Sphere{Vec(0, 0, -1.5), 0.5, glass},

        new Sphere{Vec(0.5, -0.2, -2.5), 0.8, metal_slv},
        new Sphere{Vec(-1.0, -0.5, -1.0), 0.5, matte_blu},
        new Sphere{Vec(1.5, -0.4, -0.5), 0.6, metal_gld},
    };

    const int samples_per_pixel{30};

    const auto start{std::chrono::high_resolution_clock::now()};

    std::cout << "Threads available: " << omp_get_max_threads();
    omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel for schedule(dynamic)
    for (int j = img_height - 1; j >= 0; --j) {
        std::vector<Vec> row_buff(img_width);
        for (int i = 0; i < img_width; ++i) {

            Vec pixel_color(0, 0, 0); // An empty "color bucket" for this pixel

            for (int s = 0; s < samples_per_pixel; ++s) {
                const auto u =
                    (double(i) + random_double(0, 1)) / double(img_width);
                const auto v =
                    (double(j) + random_double(0, 1)) / double(img_height);

                const Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, objs, 15);
            }

            row_buff[i] = pixel_color;
        }
        for (int i{}; i < img_width; ++i) {
            int ind{(img_height - 1 - j) * img_width + i};
            img_buff[ind] = row_buff[i];
        }
    }

    const auto end{std::chrono::high_resolution_clock::now()};
    const auto elapsed{
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)};
    std::cerr << "\nTook " << elapsed.count() / 1000 << " seconds" << std::endl;

    std::ofstream img_file("render_recent.ppm");

    img_file << "P3\n" << img_width << " " << img_height << "\n255\n";

    const double scale = 1.0 / samples_per_pixel;

    for (const Vec& pixel_c : img_buff) {
        const double r = std::sqrt(scale * pixel_c.u);
        const double g = std::sqrt(scale * pixel_c.v);
        const double b = std::sqrt(scale * pixel_c.w);

        img_file << static_cast<int>(256 * std::clamp(r, 0.0, 0.999)) << " "
                 << static_cast<int>(256 * std::clamp(g, 0.0, 0.999)) << " "
                 << static_cast<int>(256 * std::clamp(b, 0.0, 0.999)) << " ";
    }

    img_file.flush();
    img_file.close();
    return 0;
}
