#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
class vec3
{
  double e[3];

public:
  constexpr vec3() : e{0, 0, 0} {}
  constexpr vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  vec3 &operator+=(const vec3 &v)
  {
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();
    return *this;
  }
  vec3 &operator*=(double t)
  {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }
  vec3 &operator/=(double t)
  {
    return *this *= (1 / t);
  }
  double length_squared() const
  {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }
  double length() const
  {
    return std::sqrt(length_squared());
  }
  bool near_zero() const
  {
    auto s = 1e-8;

    return (std::fabs(e[0]) < s && std::fabs(e[1]) < s && std::fabs(e[2]) < s);
  }
};

inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
  return out << v[0] << ' ' << v[1] << ' ' << v[2];
}
inline vec3 operator+(const vec3 &v, const vec3 &u)
{
  return vec3(v[0] + u[0], v[1] + u[1], v[2] + u[2]);
}
inline vec3 operator-(const vec3 &v, const vec3 &u)
{
  return vec3(v[0] - u[0], v[1] - u[1], v[2] - u[2]);
}
inline vec3 operator*(const vec3 &v, const vec3 &u)
{
  return vec3(v[0] * u[0], v[1] * u[1], v[2] * u[2]);
}
inline vec3 operator*(const vec3 &v, double t)
{
  return vec3(t * v[0], t * v[1], t * v[2]);
}

inline vec3 operator*(double t, const vec3 &v)
{
  return vec3(t * v[0], t * v[1], t * v[2]);
}
inline vec3 operator/(const vec3 &v, double t)
{
  return v * (1 / t);
}
inline double dot(const vec3 &v, const vec3 &u)
{
  return v[0] * u[0] + v[1] * u[1] + v[2] * u[2];
}
inline vec3 cross(const vec3 &v, const vec3 &u)
{
  return vec3(
      v[1] * u[2] - v[2] * u[1],
      v[2] * u[0] - v[0] * u[2],
      v[0] * u[1] - v[1] * u[0]);
}
inline vec3 unit_vector(const vec3 &v)
{
  return v / v.length();
}

inline vec3 random()
{
  return vec3(random_double(), random_double(), random_double());
}

inline vec3 random(double min, double max)
{
  return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

inline vec3 random_unit_vector()
{
  // random vector uniformly distributed on unit sphere surface https://mathworld.wolfram.com/SpherePointPicking.html
  auto theta = random_double(0, 2 * PI);
  auto phi = std::acos(random_double(-1, 1));
  auto sinPhi = std::sin(phi);
  auto cosPhi = std::cos(phi);
  auto sinTheta = std::sin(theta);
  auto cosTheta = std::cos(theta);

  return vec3(sinPhi * cosTheta, sinPhi * sinTheta, cosPhi);
}
inline vec3 random_in_unit_disk()
{
  auto y = random_double(-1, 1);
  auto max_x = std::sqrt(1 - (y * y));
  auto x = random_double(-max_x, max_x);
  return vec3(x, y, 0.0);
}
inline vec3 random_on_hemisphere(const vec3 &normal)
{
  vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0)
  {
    return on_unit_sphere;
  }
  else
  {
    return -on_unit_sphere;
  }
}

inline vec3 reflect(const vec3 &v, const vec3 &n)
{
  return v - 2 * dot(v, n) * n;
}

inline vec3 refract(const vec3 &uv, const vec3 &normal, double etai_over_etat)
{
  auto cos_theta = std::fmin(dot(-uv, normal), 1);
  vec3 r_out_perpendicular = etai_over_etat * (uv + cos_theta * normal);
  vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perpendicular.length_squared())) * normal;
  return r_out_perpendicular + r_out_parallel;
}

#endif