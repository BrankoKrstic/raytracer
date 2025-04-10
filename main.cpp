#include <iostream>

#include "color.h"

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

int main()
{

  int image_width = 256;
  int image_height = 256;
  std::cout << "P3\n"
            << image_width << ' ' << image_height << "\n255\n";

  for (int y = 0; y < image_height; y++)
  {
    print_progress(y * 100 / image_height);
    for (int x = 0; x < image_width; x++)
    {
      auto c = color(double(x) / (image_width - 1), double(y) / (image_height - 1), 0.0);
      write_color(std::cout, c);
    }
  }
}
