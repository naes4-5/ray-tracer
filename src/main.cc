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
    const int image_width = 400;
    const int image_height = 225;

    std::ofstream imageFile("out/render_impl_planes.ppm");
    imageFile << "P3\n" << image_width << " " << image_height << "\n255\n";

    double viewport_height = 2.0;
    double viewport_width =
        viewport_height * (double(image_width) / image_height);
    double focal_length = 1.0; // Distance from camera to viewport

    HittableList objs{
        new Sphere(Vec(0.7, 0.2, -1), 0.3),
        new Sphere(Vec(-0.3, 0, -1), 0.4),
        new Plane(Vec(0, -0.5, 0), Vec(0, 1, 0)),
    };

    Vec origin = Vec(0, 0, 0);
    Vec horizontal = Vec(viewport_width, 0, 0);
    Vec vertical = Vec(0, viewport_height, 0);

    Vec lower_left_corner = origin - (horizontal * 0.5) - (vertical * 0.5) -
                            Vec(0, 0, focal_length);

    // rendering
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rLines remaining: " << j << "  " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);

            Vec direction =
                lower_left_corner + (horizontal * u) + (vertical * v) - origin;
            Ray r(origin, direction);

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
