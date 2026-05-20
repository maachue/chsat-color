#pragma once

#include <concepts>

#include "../convert.h"
#include "../generic_rgb.h"

namespace color {
template <std::floating_point T>
struct converter<standard_rgb<T>, linear_rgb<T>> {
  constexpr static linear_rgb<T> convert(standard_rgb<T> const &from) {
    linear_rgb<T> result{};

    for (int i = 0; i < 3; ++i) {
      T val_ = from.data[i];

      if (val_ <= T(0.04045)) {
        result.data[i] = val_ / T(12.92);
      } else {
        result.data[i] = math::pow((val_ + T(0.055)) / T(1.055), T(2.4));
      }
    }

    return result;
  }
};

template <std::floating_point T>
struct converter<linear_rgb<T>, standard_rgb<T>> {
  constexpr static standard_rgb<T> convert(linear_rgb<T> const &from) {
    standard_rgb<T> result{};

    for (int i = 0; i < 3; ++i) {
      T val_ = from.data[i];

      if (val_ <= T(0.0031308)) {
        result.data[i] = val_ * T(12.92);
      } else {
        result.data[i] = (T(1.055) * math::pow(val_, T(1) / T(2.4))) - T(0.055);
      }
    }

    return result;
  }
};
} // namespace color