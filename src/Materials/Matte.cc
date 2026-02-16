#include "Materials/Matte.hh"
#include "util.hh"

Matte::Matte(const Vec& c) : albedo(c) {}

bool Matte::scatter(const Ray& ray_in, hit_record& rec, Vec& attenuation,
                    Ray& scattered) const {
    (void)ray_in;
    Vec dir{rec.N + rand_in_unit_sphere()};
    attenuation = albedo;
    scattered = Ray(rec.P, dir);
    return true;
}
