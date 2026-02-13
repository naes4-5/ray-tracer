#include "Camera.hh"
#include "Hittable.hh"
#include "HittableList.hh"
#include "Plane.hh"
#include "Ray.hh"
#include "Sphere.hh"
#include <cmath>
#include <cust_vector.hh>
#include <fstream>
#include <iostream>

int main() {
    // 16:9 ratio
    const int image_width = 1920;
    const int image_height = 1080;

    std::ofstream imageFile("out/render_temp.ppm");
    imageFile << "P3\n" << image_width << " " << image_height << "\n255\n";

    Vec lookfrom(0, 0, 5); // Camera at origin
    Vec lookat(0, 0, -1);  // Looking down the negative Z-axis
    Vec vup(0, 1, 0);      // "Up" is toward the sky
    double vfov{45.0};     // Height of 2.0
    double aspect_ratio{double(image_width) / image_height};

    Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio);

    HittableList objs{
        new Sphere(Vec(0.7, 0.2, -1), 0.3),
        new Sphere(Vec(-0.3, 0, -1), 0.4),
        new Sphere(Vec(0.8, -0.3, -1.3), 0.2),
        new Sphere(Vec(-1.5, 0.8, -1), 0.1),
        new Sphere(Vec(-1.5, -1, 1), 1),
        new Plane(Vec(0, -0.5, 0), Vec(0, 1, 0)),
    };

    // rendering
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rLines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u{double(i) / (image_width - 1)};
            auto v{double(j) / (image_height - 1)};

            Ray r{cam.get_ray(u, v)};

            hit_record rec{};

            if (objs.hit(r, 0.001, INFINITY, rec)) {

                // Convert Normal direction (-1 to 1) to RGB
                int ir = static_cast<int>(255.999 * 0.5 * (rec.N.x() + 1));
                int ig = static_cast<int>(255.999 * 0.5 * (rec.N.y() + 1));
                int ib = static_cast<int>(255.999 * 0.5 * (rec.N.z() + 1));
                imageFile << ir << " " << ig << " " << ib << "\n";
            } else {
                // Missed: Draw the background sky gradient
                Vec unit_direction = r.dir.unit_vector();
                auto bg_r = 0.5 * (unit_direction.y() + 1.0);

                int ir =
                    static_cast<int>(255 * ((1.0 - bg_r) * 1.0 + bg_r * 0.6));
                int ig =
                    static_cast<int>(255 * ((1.0 - bg_r) * 1.0 + bg_r * 0.8));
                int ib = 255;
                imageFile << ir << " " << ig << " " << ib << "\n";
            }
        }
    }
    std::cerr << '\n';
    return 0;
}
