#pragma once
#include "WorldBuilding/Ray.hh"

class Camera {
  public:
    Vec orig;
    Vec llc;
    Vec hori;
    Vec vert;

    Camera(const Vec& lookfrom, const Vec& lookat, const Vec& vertical,
           const double vfov, const double aspect_ratio);

    Ray get_ray(const double u, const double v) const;
};
