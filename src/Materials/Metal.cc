#include "Materials/Metal.hh"
#include "util.hh"

Metal::Metal(const Vec& c, const double f)
    : albedo(c), fuzz(f < 0.0001 ? 0.0001 : f) {}

bool Metal::scatter(const Ray& ray_in, hit_record& rec, Vec& attenuation,
                    Ray& scattered) const {
    Vec ref{reflect(ray_in.dir.unit_vector(), rec.N)};
    attenuation = albedo;
    scattered =
        Ray(rec.P + (rec.N + 0.0001), ref + rand_in_unit_sphere() * fuzz);
    return scattered.dir.dot(rec.N) > 0;
}
