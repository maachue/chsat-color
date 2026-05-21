#pragma once

#include <array>
#include <cmath>
#include <numbers>

#include <gcem.hpp>

namespace color::math {
template <typename T> using vec3 = std::array<T, 3>;

template <typename T> using matrix3x3 = std::array<std::array<T, 3>, 3>;

template <typename T>
constexpr vec3<T> vec_multiply_matrix(vec3<T> const &vec,
                                      matrix3x3<T> const &matrix) {
  vec3<T> result{};

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      result[i] += vec[j] * matrix[i][j];
    }
  }

  return result;
}

//=========================================================================//
//                    Some wrapper for math functions ....                 //
//         allowed calculate at compile-time or runtime specific           //
//=========================================================================//

template <typename T> constexpr T rad_to_deg(T const val) {
  return val * (T(180) / std::numbers::pi_v<T>);
}
template <typename T> constexpr T deg_to_rad(T const val) {
  return val * (std::numbers::pi_v<T> / T(180));
}

template <typename T> constexpr T abs(T const val) {
  if consteval {
    return gcem::abs(val);
  } else {
    return std::abs(val);
  }
}

template <typename Tx, typename Ty>
constexpr auto pow(Tx const &x, Ty const &y) {
  if consteval {
    return gcem::pow(x, y);
  } else {
    return std::pow(x, y);
  }
}

template <typename Tx> constexpr auto sqrt(Tx const &x) {
  if consteval {
    return gcem::sqrt(x);
  } else {
    return std::sqrt(x);
  }
}

template <typename Tx, typename Ty>
constexpr auto atan2(Ty const &y, Tx const &x) {
  if consteval {
    return gcem::atan2(y, x);
  } else {
    return std::atan2(y, x);
  }
}

template <typename Tx> constexpr auto sin(Tx const &x) {
  if consteval {
    return gcem::sin(x);
  } else {
    return std::sin(x);
  }
}

template <typename Tx> constexpr auto cos(Tx const &x) {
  if consteval {
    return gcem::cos(x);
  } else {
    return std::cos(x);
  }
}

template <typename Tx> constexpr auto exp(Tx const &x) {
  if consteval {
    return gcem::exp(x);
  } else {
    return std::exp(x);
  }
}
} // namespace color::math
