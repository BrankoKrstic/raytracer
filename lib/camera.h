#ifndef CAMERA_H
#define CAMERA_H

#include "hit.h"
#include "color.h"
#include "interval.h"

constexpr static double focal_length = 2.0;
constexpr static vec3 camera_center = vec3(0, 0, 0);

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
        auto pixel_center = pixel100_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
        auto ray_direction = pixel_center - camera_center;
        auto r = ray(camera_center, ray_direction);

        color pixel_color = ray_color(r, world);
        write_color(std::cout, pixel_color);
      }
    }
  }

private:
  vec3 pixel100_loc;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
  int image_width = 1000;
  double ratio = 16.0 / 9.0;
  double viewport_height = 2.0;
  int image_height;
  double viewport_width;

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
  }
  color ray_color(const ray &r, const hittable &world)
  {
    hit_record rec;
    if (world.hit(r, interval(0, POSITIVE_INFINITY), rec))
    {
      return 0.5 * (rec.normal + vec3(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }
};

#endif