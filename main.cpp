#include <iostream>
#include "lib.h";

int main()
{

  int image_width = 256;
  int image_height = 256;
  std::cout << "P3\n"
            << image_width << ' ' << image_height << "\n255\n";

  for (int y = 0; y < image_height; y++)
  {
    int scanlines = image_height;
    int done = y;
    int progress = done * 100 / scanlines;
    std::clog << '\r';
    for (int i = 0; i < 100; i++)
    {
      if (i <= progress)
      {
        std::clog << 'X';
      }
      else
      {
        std::clog << '-';
      }
    }
    std::clog << ' ' << std::flush;
    for (int x = 0; x < image_width; x++)
    {
      auto r = double(x) / (image_width - 1);
      auto g = double(y) / (image_height - 1);
      auto b = 0.0;

      int ir = int(255.999 * r);
      int ig = int(255.999 * g);
      int ib = int(255.999 * b);

      std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
}
