#ifndef SPHERE_H
#define SPHERE_H

#include "hit.h"
#include "vec3.h"

class sphere : public hittable
{
public:
  sphere(const vec3 &center, double radius) : center{center}, radius{std::fmax(0.0, radius)} {}
  bool hit(const ray &r, interval ray_t, hit_record &rec) const override
  {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto h = dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = h * h - a * c;
    if (discriminant < 0)
    {
      return false;
    }
    auto sqrtd = std::sqrt(discriminant);

    auto root = (h - sqrtd) / a;
    if (!ray_t.contains(root))
    {
      root = (h + sqrtd) / a;
      if (!ray_t.contains(root))
      {
        return false;
      }
    }
    rec.t = root;
    rec.point = r.at(rec.t);

    vec3 outward_normal = (rec.point - center) / radius;
    rec.set_face_notmal(r, outward_normal);
    return true;
  }

private:
  vec3 center;
  double radius;
};

#endif
