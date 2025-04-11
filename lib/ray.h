#ifndef RAY_H;
#define RAY_H ;

#include "vec3.h"

class ray
{
public:
  ray() {}
  ray(const vec3 &origin, const vec3 &direction) : orig(origin), dir(direction) {}
  const vec3 &origin()
  {
    return orig;
  }
  const vec3 &direction()
  {
    return dir;
  }
  const vec3 &at(double t) const
  {
    return orig + dir * t;
  }

private:
  vec3 orig;
  vec3 dir;
};

#endif