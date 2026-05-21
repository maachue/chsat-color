#pragma once

#include <concepts>

#include "../chsat_m.h"
#include "../convert.h"

#include "../lab.h"
#include "../xyz.h"

namespace color {
namespace wp {
template <typename T> struct D65_internal {
  T x = T(95.0489) / T(100);
  T y = T(100.0) / T(100);
  T z = T(108.8840) / T(100);
};
} // namespace wp

namespace internal {
template <typename T> constexpr auto fn_xyz_lab(T const val) {
  constexpr T g = T(T(6) / T(29));

  if (val > math::pow(g, 3)) {
    return math::pow(val, T(1) / T(3));
  } else {
    return (T(1) / T(3)) * val * math::pow(g, -2) + (T(4) / T(29));
  }
}
} // namespace internal

template <std::floating_point T> struct converter<xyzd65<T>, labd65<T>> {
  constexpr static labd65<T> convert(xyzd65<T> const &from) {
    constexpr wp::D65_internal<T> d65_xyz{};
    T xn = internal::fn_xyz_lab(from.x() / d65_xyz.x);
    T yn = internal::fn_xyz_lab(from.y() / d65_xyz.y);
    T zn = internal::fn_xyz_lab(from.z() / d65_xyz.z);

    return labd65<T>{
        {(T(116) * yn) - T(16), T(500) * (xn - yn), T(200) * (yn - zn)}};
  }
};
} // namespace color
