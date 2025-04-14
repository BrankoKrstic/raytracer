
#include "lib.h"
#include "sphere.h"
#include "camera.h"

int main()
{
  camera cam;
  hittable_list world;

  world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(vec3(0, -100.5, -1), 100));
  world.add(make_shared<sphere>(vec3(-1, -1, -3), 0.5));
  world.add(make_shared<sphere>(vec3(2, 0, -3), 0.7));

  cam.render(world);
}
