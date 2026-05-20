#pragma once

#include "chsat_m.h"
#include "whitepoint.h"

namespace color {
template <typename T, wp::wpoint Wp> struct basic_lab {
  using value_type = T;
  using wp = Wp;

  math::vec3<T> data;

  constexpr T const &l() const { return data[0]; }
  constexpr T const &a() const { return data[1]; }
  constexpr T const &b() const { return data[2]; }

  T &l() { return data[0]; }
  T &a() { return data[1]; }
  T &b() { return data[2]; }
};

template <typename T> using labd65 = basic_lab<T, wp::D65>;

template <typename T> using labd50 = basic_lab<T, wp::D50>;
} // namespace color