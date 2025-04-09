#include <iostream>

int main()
{

  int image_width = 256;
  int image_height = 256;

  std::cout << "P3\n"
            << image_width << ' ' << image_height << "\n255\n";

  for (int y = 0; y < image_height; y++)
  {
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
