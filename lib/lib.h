#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
constexpr double NEGATIVE_INFINITY = -POSITIVE_INFINITY;

constexpr double PI = 3.1415926535897932385;

// Utility Functions

constexpr inline double degrees_to_radians(double degrees)
{
  return degrees * PI / 180.0;
}

inline double random_double()
{
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

inline double random_double(double min, double max)
{
  return min + (max - min) * random_double();
}

// Common Headers

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif