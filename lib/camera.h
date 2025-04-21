#ifndef CAMERA_H
#define CAMERA_H

#include "hit.h"
#include "color.h"
#include "interval.h"
#include "material.h"

constexpr static double focal_length = 1.0;
constexpr static vec3 camera_center = vec3(0, 0, 0);
constexpr static int samples_per_pixel = 100;
constexpr int max_depth = 10; // Maximum number of ray bounces into scene

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
          try
          {
            ray r = get_ray(y, x);
            // Block of code to try
            pixel_color += ray_color(r, max_depth, world);
          }
          catch (...)
          {
            std::cout << "EXCEPTION\n";
            // Block of code to handle errors
          }
        }
        write_color(std::cout, pixel_color * pixel_samples_scale);
      }
    }
  }
  ray get_ray(int y, int x)
  {
    auto offset = sample_disk();
    auto pixel_sample = pixel100_loc + ((x + offset.x()) * pixel_delta_u) + ((y + offset.y()) * pixel_delta_v);
    auto ray_direction = pixel_sample - camera_center;
    return ray(camera_center, ray_direction);
  }
  vec3 sample_square() const
  {
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
  }
  vec3 sample_disk() const
  {
    return random_in_unit_disk();
  }

private:
  vec3 pixel100_loc;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
  int image_width = 500;
  double ratio = 16.0 / 9.0;
  double viewport_height = 2.0;
  int image_height;
  double viewport_width;
  double pixel_samples_scale;

  void init()
  {
    image_height = int(image_width / ratio);
    viewport_width = viewport_height * (double(image_width) / image_height);
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_v / 2 - viewport_u / 2;
    pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    pixel_samples_scale = 1.0 / samples_per_pixel;
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