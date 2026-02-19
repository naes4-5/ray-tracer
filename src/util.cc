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

bool hit_outside(const Vec& P, const Vec& N) { return P.dot(N) < 0.0; }

Vec normal_dir(const hit_record& rec) {
    return rec.front_face ? rec.N : rec.N * -1.0;
}
