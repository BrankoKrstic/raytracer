#ifndef CAMERA_H
#define CAMERA_H

#include "hit.h"
#include "color.h"
#include "interval.h"
#include "material.h"
#include <thread>
#include <vector>
constexpr static double fov_vertical = 20.0;

constexpr static vec3 lookfrom = vec3(13, 2, 3);
;
constexpr static vec3 lookat = vec3(0, 0, 0);
constexpr static vec3 vup = vec3(0, 1, 0);

constexpr static double defocus_angle = 0.6;
constexpr static double focus_dist = 10.0;

constexpr static int samples_per_pixel = 500;
constexpr int max_depth = 50; // Maximum number of ray bounces into scene

void print_progress(int progress_percent)
{
  std::clog << '\r';
  for (int i = 0; i < 100; i++)
  {
    if (i <= progress_percent)
    {
      std::clog << 'X';
    }
    else
    {
      std::clog << '-';
    }
  }
  std::clog << ' ' << std::flush;
}

class camera
{
public:
  void render(const hittable &world)
  {
    init();

    std::cout
        << "P3\n"
        << image_width << ' ' << image_height << "\n255\n";

    for (int y = 0; y < image_height; y++)
    {
      print_progress(y * 100 / image_height);
      for (int x = 0; x < image_width; x++)
      {
        color pixel_color(0, 0, 0);
        for (int sample = 0; sample < samples_per_pixel; sample++)
        {
          ray r = get_ray(y, x);
          // Block of code to try
          pixel_color += ray_color(r, max_depth, world);
        }
        write_color(std::cout, pixel_color * pixel_samples_scale);
      }
    }
  }
  ray get_ray(int y, int x)
  {
    auto offset = sample_disk();
    auto pixel_sample = pixel100_loc + ((x + offset.x()) * pixel_delta_u) + ((y + offset.y()) * pixel_delta_v);
    auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;
    return ray(ray_origin, ray_direction);
  }
  vec3 sample_square() const
  {
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
  }
  vec3 sample_disk() const
  {
    return random_in_unit_disk();
  }
  vec3 defocus_disk_sample()
  {
    auto p = random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
  };

private:
  int image_height;
  vec3 pixel100_loc;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
  vec3 u, v, w;
  int image_width = 1200;
  double ratio = 16.0 / 9.0;
  vec3 center;
  double viewport_width;
  double pixel_samples_scale;
  vec3 defocus_disk_u;
  vec3 defocus_disk_v;

  void init()
  {
    image_height = int(image_width / ratio);
    auto theta = degrees_to_radians(fov_vertical);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2 * h * focus_dist;
    viewport_width = viewport_height * (double(image_width) / image_height);

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    auto viewport_u = viewport_width * u;
    auto viewport_v = -viewport_height * v;
    pixel_samples_scale = 1.0 / samples_per_pixel;
    center = lookfrom;
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = center - focus_dist * w - viewport_v / 2 - viewport_u / 2;
    pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
  }
  color ray_color(const ray &r, int depth, const hittable &world)
  {
    if (depth <= 0)
    {
      return color(0, 0, 0);
    }
    hit_record rec;
    if (world.hit(r, interval(0.001, POSITIVE_INFINITY), rec))
    {
      ray scattered;
      color attenuation;
      if (rec.mat->scatter(r, rec, attenuation, scattered))
      {
        return attenuation * ray_color(scattered, depth - 1, world);
      }
      return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }
};

#endif