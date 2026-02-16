#include "util.hh"

Vec rand_in_unit_sphere() {
    while (true) {
        Vec v{random_double(-1, 1), random_double(-1, 1), random_double(-1, 1)};
        if (v.mag() >= 1)
            continue;
        return v;
    }
}

const Vec reflect(const Vec& v, const Vec& n) {
    return v - n * (2.0 * v.dot(n));
}
