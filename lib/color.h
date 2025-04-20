#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"

using color = vec3;

double linear_to_gamma(double linear_component)
{
  if (linear_component > 0.0)
  {
    return std::sqrt(linear_component);
  }
  return 0.0;
}

void write_color(std::ostream &out, const color &pixel_color)
{
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  auto gr = linear_to_gamma(r);
  auto gg = linear_to_gamma(g);
  auto gb = linear_to_gamma(b);

  // Translate the [0,1] component values to the byte range [0,255].
  static const interval interval(0.0, 0.999);
  int rbyte = int(256 * interval.clamp(gr));
  int gbyte = int(256 * interval.clamp(gg));
  int bbyte = int(256 * interval.clamp(gb));

  // Write out the pixel color components.
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
#endif