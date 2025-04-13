#ifndef INTERVAL_H
#define INTERVAL_H

#include "lib.h"

class interval
{
public:
  double min, max;
  interval() : min{POSITIVE_INFINITY}, max{NEGATIVE_INFINITY} {}
  interval(double min, double max) : min{min}, max{max} {}
  double size() const
  {
    return max - min;
  }
  bool contains(double x) const
  {
    return min <= x && x <= max;
  }
  bool surrounds(double x) const
  {
    return min < x && x < max;
  }
  static const interval empty, universe;
};

const interval interval::empty = interval(POSITIVE_INFINITY, NEGATIVE_INFINITY);
const interval interval::universe = interval(NEGATIVE_INFINITY, POSITIVE_INFINITY);

#endif