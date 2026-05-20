#pragma once

#include "chsat_m.h"

#include "whitepoint.h"

namespace color {
template <typename T, wp::wpoint Wp> struct basic_xyz {
  using value_type = T;
  using wp = Wp;

  math::vec3<T> data;

  constexpr T const &x() const { return data[0]; }
  constexpr T const &y() const { return data[1]; }
  constexpr T const &z() const { return data[2]; }

  T &x() { return data[0]; }
  T &y() { return data[1]; }
  T &z() { return data[2]; }
};

template <typename T> using xyzd65 = basic_xyz<T, wp::D65>;
} // namespace color