#include "Materials/Metal.hh"
#include "util.hh"

Metal::Metal(const Vec& c, const double f) : albedo(c), fuzz(f < 1 ? f : 1) {}

bool Metal::scatter(const Ray& ray_in, hit_record& rec, Vec& attenuation,
                    Ray& scattered) const {
    Vec ref{reflect(ray_in.dir, rec.N)};
    attenuation = albedo;
    scattered = Ray(rec.P, ref + rand_in_unit_sphere() * fuzz);
    return scattered.dir.dot(rec.N) > 0;
}
