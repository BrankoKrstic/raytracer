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
#endif