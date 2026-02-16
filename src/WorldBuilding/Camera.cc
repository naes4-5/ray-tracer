#include "WorldBuilding/Camera.hh"
#include <cmath>

Camera::Camera(const Vec& lookfrom, const Vec& lookat, const Vec& vertical,
               const double vfov, const double aspect_ratio)
    : orig(lookfrom) {
    auto theta{vfov * (M_PI / 180)};
    auto view_h{2 * tan(theta / 2)};
    auto view_w{view_h * aspect_ratio};

    auto w{(lookfrom - lookat).unit_vector()}; // +z vector
    auto u{vertical.cross(w).unit_vector()};   // +x vector
    auto v{w.cross(u)};                        // +y vector

    hori = u * view_w;                            // horizontal width (vec)
    vert = v * view_h;                            // vertical height  (vec)
    llc = orig - (hori / 2.0) - (vert / 2.0) - w; // w for focal lengh
}

Ray Camera::get_ray(const double u, const double v) const {
    return Ray(orig, llc + (hori * u) + (vert * v) - orig);
}
