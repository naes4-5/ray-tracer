#include "Hittable/Material.hh"

class Metal : public Material {
  public:
    Vec albedo;
    double fuzz;

    Metal(const Vec& c, const double f);

    virtual bool scatter(const Ray& ray_in, hit_record& rec, Vec& attenuation,
                         Ray& scattered) const override;
};
