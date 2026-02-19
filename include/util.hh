#pragma once
#include "Hittable/Hittable.hh"
#include "WorldBuilding/Vec.hh"
#include "omp.h"
#include <random>

inline double random_double(double min, double max) {
    // seed with both the clock and the thread id to ensure every thread is
    // unique and local to that thread
    thread_local static std::mt19937 generator(std::random_device{}() +
                                               omp_get_thread_num());
    thread_local static std::uniform_real_distribution<double> distribution(
        min, max);
    return distribution(generator);
}

Vec rand_in_unit_sphere();
const Vec reflect(const Vec& v, const Vec& n);
bool hit_outside(const Vec& P, const Vec& N);
Vec normal_dir(const hit_record& rec);
