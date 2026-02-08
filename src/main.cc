#include "Ray.h"
#include <fstream>
#include <iostream>

double collision(const Vec& cen, double rad, const Ray& ray) {
    Vec c_to_ray = ray.orig - cen;
    auto a = ray.dir.dot(ray.dir);
    auto b = 2.0 * ray.dir.dot(c_to_ray);
    auto c = c_to_ray.dot(c_to_ray) - rad * rad;
    auto disc = b * b - 4.0 * a * c;

    if (disc < 0) {
        return -1.0;
    }
    return (-b - std::sqrt(disc)) / (2.0 * a);
}

int main() {
    // 1. IMAGE SETUP
    const int image_width = 400;
    const int image_height = 225; // Maintains 16:9 ratio

    std::ofstream imageFile("render_bg_test.ppm");
    imageFile << "P3\n" << image_width << " " << image_height << "\n255\n";

    // 2. CAMERA / VIEWPORT SETUP
    // The viewport is the "window" into our 3D world
    double viewport_height = 2.0;
    double viewport_width =
        viewport_height * (double(image_width) / image_height);
    double focal_length = 1.0; // Distance from camera to viewport

    Vec origin = Vec(0, 0, 0);
    Vec horizontal = Vec(viewport_width, 0, 0);
    Vec vertical = Vec(0, viewport_height, 0);
    // Lower-left corner is our starting point for scanning
    Vec lower_left_corner = origin - (horizontal * 0.5) - (vertical * 0.5) -
                            Vec(0, 0, focal_length);

    // 3. THE RENDERING LOOP
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rLines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {

            // Normalize coordinates: u and v are 0.0 to 1.0
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);

            // Construct the Ray
            // Target = LowerLeft + (horizontal offset) + (vertical offset)
            Vec direction =
                lower_left_corner + (horizontal * u) + (vertical * v) - origin;
            Ray r(origin, direction);

            // 4. COLOR DETERMINATION
            double t = collision(Vec(0, 0, -1), 0.5, r);

            if (t > 0.0) {
                // We hit the sphere!
                // Find the hit point P and the surface normal N
                Vec P = r.at(t);
                Vec N = (P - Vec(0, 0, -1)).unit_vector();

                // Convert Normal direction (-1 to 1) to RGB (0 to 255)
                int ir = static_cast<int>(255.999 * 0.5 * (N.x() + 1));
                int ig = static_cast<int>(255.999 * 0.5 * (N.y() + 1));
                int ib = static_cast<int>(255.999 * 0.5 * (N.z() + 1));
                imageFile << ir << " " << ig << " " << ib << "\n";
            } else {
                // Missed: Draw the background sky gradient
                Vec unit_direction = r.dir.unit_vector();
                auto t_bg = 0.5 * (unit_direction.y() + 1.0);

                int ir =
                    static_cast<int>(255 * ((1.0 - t_bg) * 1.0 + t_bg * 0.5));
                int ig =
                    static_cast<int>(255 * ((1.0 - t_bg) * 1.0 + t_bg * 0.7));
                int ib = 255;
                imageFile << ir << " " << ig << " " << ib << "\n";
            }
        }
    }
    std::cerr << '\n';
    return 0;
}
