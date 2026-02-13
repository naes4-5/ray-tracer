#pragma once
#include "Hittable.hh"
#include <cmath>

class Sphere : public Hittable {
  public:
    Vec center;
    double rad;

    Sphere(const Vec c, double r) : center(c), rad(r) {}

    virtual bool hit(const Ray& ray, const double t_min, const double t_max,
                     hit_record& rec) const override {
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
        rec.P = ray.at(rec.t);
        rec.N = (rec.P - center).unit_vector();
        return true;
    }
};
