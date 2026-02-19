#include "Materials/Metal.hh"
#include "util.hh"

Metal::Metal(const Vec& c, const double f)
    : albedo(c), fuzz(f < 0.0001 ? 0.0001 : f) {}

bool Metal::scatter(const Ray& ray_in, hit_record& rec, Vec& attenuation,
                    Ray& scattered) const {
    attenuation = albedo;
    Vec dir{reflect(ray_in.dir.unit_vector(), rec.N)};
    scattered = Ray(rec.P + normal_dir(rec) * 0.0001,
                    dir + rand_in_unit_sphere() * fuzz);
    return scattered.dir.dot(rec.N) > 0;
}
