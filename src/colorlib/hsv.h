#pragma once

#include "chsat_m.h"

#include "whitepoint.h"

namespace color {
template <typename T, typename Wp> struct basic_hsv {
  math::vec3<T> data;

  T &h() { return data[0]; }
  T &s() { return data[1]; }
  T &v() { return data[2]; }
  const T &h() const { return data[0]; }
  const T &s() const { return data[1]; }
  const T &v() const { return data[2]; }
};

template <typename T> using hsvd65 = basic_hsv<T, wp::D65>;
} // namespace color
