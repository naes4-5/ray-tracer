#include "Materials/Dielectric.hh"
#include "util.hh"
#include <cmath>

#define AIR_RI 1.0

Dielectric::Dielectric() : ri(1.0) {}
Dielectric::Dielectric(const double r) : ri(r) {}

double Dielectric::reflectance(const double cos) const {
    const double R0{pow((1.0 - ri) / (AIR_RI + ri), 2.0)};
    return R0 + (1 - R0) * pow(1 - cos, 5);
}

Vec Dielectric::refract(const Vec& R_perp, const Vec& n) const {
    const auto R_para{(n * -1.0) * std::sqrt(1.0 - R_perp.dot(R_perp))};
    return R_perp + R_para;
}

bool Dielectric::scatter(const Ray& ray_in, hit_record& rec, Vec& attenuation,
                         Ray& scattered) const {
    attenuation = Vec{1.0, 1.0, 1.0};
    const auto Ru{ray_in.dir.unit_vector()};
    const auto nu{normal_dir(rec)};
    const auto cost{std::fmin((Ru * -1.0).dot(nu), 1.0)};
    const auto sint{std::sqrt(std::max(0.0, 1 - pow(cost, 2)))};
    const auto refrac_ratio{rec.front_face ? AIR_RI / ri : ri / AIR_RI};
    const auto R_perp{(Ru + nu * cost) * refrac_ratio};
    const bool cannot_refract{refrac_ratio * sint > 1.0 ||
                              R_perp.dot(R_perp) > 1.0};
    Vec dir;
    if (cannot_refract || reflectance(cost) > random_double(0, 1)) {
        dir = reflect(ray_in.dir.unit_vector(), rec.N);
    } else
        dir = refract(R_perp, rec.N);
    scattered = Ray(rec.P + (dir * 0.0001), dir);
    return true;
}
