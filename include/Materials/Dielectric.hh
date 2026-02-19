#include "Hittable/Material.hh"

class Dielectric : public Material {
  private:
    double reflectance(const double cos) const;
    Vec refract(const Vec& R_perp, const Vec& n) const;

  public:
    double ri;

    Dielectric();
    Dielectric(const double r);

    virtual bool scatter(const Ray& ray_in, hit_record& rec, Vec& attenuation,
                         Ray& scattered) const override;
};
