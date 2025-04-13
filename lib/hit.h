#ifndef HITTABLE_H
#define HITTABLE_H

#include <vector>
#include "ray.h"

class hit_record
{
public:
  vec3 point;
  vec3 normal;
  double t;
  bool front_face;

  void set_face_notmal(const ray &r, const vec3 &outward_normal)
  {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable
{
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;
};

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable
{
public:
  std::vector<shared_ptr<hittable>> objects;
  hittable_list() {}
  hittable_list(shared_ptr<hittable> object) { add(object); }
  void clear()
  {
    objects.clear();
  }
  void add(shared_ptr<hittable> object)
  {
    objects.push_back(object);
  }
  bool hit(const ray &r, interval ray_t, hit_record &rec) const override
  {
    hit_record temp;
    bool hit_anything = false;
    auto closest_so_far = ray_t.max;

    for (const auto &object : objects)
    {
      if (object->hit(r, ray_t, temp))
      {
        hit_anything = true;
        // TODO: fill in this logic
        closest_so_far = temp.t;
        rec = temp;
      }
    }

    return hit_anything;
  }
};

#endif