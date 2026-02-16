#pragma once
#include "WorldBuilding/Vec.hh"
#include <random>

// Returns a random real number in [min, max).
inline double random_double(double min, double max) {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

Vec rand_in_unit_sphere();
const Vec reflect(const Vec& v, const Vec& n);
