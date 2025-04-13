#include <iostream>

#include "color.h"
#include "vec3.h"
#include "ray.h"

double hits_sphere(const vec3 &center, double radius, const ray &r)
{
  vec3 oc = center - r.origin();
  auto a = dot(r.direction(), r.direction());
  auto b = -2.0 * dot(r.direction(), oc);
  auto c = dot(oc, oc) - radius * radius;
  auto discriminant = b * b - 4 * a * c;

  if (discriminant < 0)
  {
    return -1.0;
  }
  else
  {
    return (-b - std::sqrt(discriminant)) / (2.0 * a);
  }
}

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

color ray_color(const ray &r)
{
  auto t = hits_sphere(vec3(0, 0, -1), 0.5, r);
  if (t > 0.0)
  {
    vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
    return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
  }

  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

constexpr static int image_width = 500;
constexpr static double ratio = 16.0 / 9.0;
constexpr static int image_height = int(image_width / ratio);

constexpr static double focal_length = 1.0;
constexpr static double viewport_height = 2.0;
constexpr static double viewport_width = viewport_height * (double(image_width) / image_height);
constexpr static vec3 camera_center = vec3(0, 0, 0);

int main()
{
  auto viewport_u = vec3(viewport_width, 0, 0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;

  auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_v / 2 - viewport_u / 2;
  auto pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  std::cout << "P3\n"
            << image_width << ' ' << image_height << "\n255\n";

  for (int y = 0; y < image_height; y++)
  {
    print_progress(y * 100 / image_height);
    for (int x = 0; x < image_width; x++)
    {
      auto pixel_center = pixel100_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
      auto ray_direction = pixel_center - camera_center;
      auto r = ray(camera_center, ray_direction);

      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }
}
