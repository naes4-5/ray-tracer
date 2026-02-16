#include "Shapes/Triangle.hh"
#include <cstdlib>

Triangle::Triangle(const Vec& a, const Vec& b, const Vec& c,
                   std::shared_ptr<Material> mat)
    : A(a), B(b), C(c), mat_ptr(mat) {
    Vec v{B - A};
    Vec u{C - A};
    N = v.cross(u).unit_vector();
    P = Plane{A, N, mat};
}

bool Triangle::hit(const Ray& ray, const double t_min, const double t_max,
                   hit_record& rec) const {
    if (!P.hit(ray, t_min, t_max, rec)) {
        return false;
    }
    Vec e1{C - A};
    Vec e2{B - A};
    Vec w{rec.P - A};

    double l{e1.dot(e1)};
    double m{e1.dot(e2)};
    double n{e2.dot(e2)};
    double X{w.dot(e1)};
    double Y{w.dot(e2)};

    double D{(l * n) - (m * m)};
    if (std::abs(D) <= 1e-8) // triangle is literally a straight line
        return false;

    double u{((X * n) - (m * Y)) / D};
    double v{((l * Y) - (X * m)) / D};
    if (u >= 0 && v >= 0 && u + v <= 1) {
        rec.N = N;
        return true;
    }
    return false;
}
