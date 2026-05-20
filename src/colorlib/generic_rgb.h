#pragma once

#include "chsat_m.h"
#include <cstdint>

namespace color {
namespace tags {
struct standard_rgb {};
struct linear_standard_rgb {};
} // namespace tags

template <typename T, typename Tag> struct basic_rgb {
  using value_type = T;
  using tag = Tag;

  math::vec3<T> data;

  constexpr T const &r() const { return data[0]; }
  constexpr T const &g() const { return data[1]; }
  constexpr T const &b() const { return data[2]; }

  T &r() { return data[0]; }
  T &g() { return data[1]; }
  T &b() { return data[2]; }
};

template <typename T> using standard_rgb = basic_rgb<T, tags::standard_rgb>;

template <typename T>
using linear_rgb = basic_rgb<T, tags::linear_standard_rgb>;

template <typename T>
constexpr standard_rgb<T> from_u8(std::uint8_t r, std::uint8_t g,
                                  std::uint8_t b) {
  return standard_rgb<T>{{static_cast<T>(r) / T(255),
                          static_cast<T>(g) / T(255),
                          static_cast<T>(b) / T(255)}};
}
} // namespace color