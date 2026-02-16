#include "Shapes/Sphere.hh"
#include <cmath>

Sphere::Sphere(const Vec c, double r, std::shared_ptr<Material> mat)
    : center(c), rad(r), mat_ptr(mat) {}

bool Sphere::hit(const Ray& ray, const double t_min, const double t_max,
                 hit_record& rec) const {
    Vec c_to_ray{ray.orig - center};
    auto a{ray.dir.dot(ray.dir)};
    auto b{2.0 * ray.dir.dot(c_to_ray)};
    auto c{c_to_ray.dot(c_to_ray) - rad * rad};
    auto disc{b * b - 4.0 * a * c};
    if (disc < 0.0)
        return false;
    auto soln{(-b - std::sqrt(disc)) / (2.0 * a)};
    if (soln < t_min || soln > t_max) {
        soln = (-b + std::sqrt(disc)) / (2.0 * a);
        if (soln < t_min || soln > t_max) {
            return false;
        }
    }
    rec.t = soln;
    rec.N = (ray.at(rec.t) - center).unit_vector();
    rec.P = ray.at(rec.t) + rec.N * 0.001;
    rec.mat_ptr = mat_ptr;
    return true;
}
