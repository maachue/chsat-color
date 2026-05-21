//============================================================================//
//                       Don't ask me formula in this file
//                 Yup, it's ΔE* but the syntax is very hard to read
//============================================================================//

#pragma once

#include <concepts>

#include "../chsat_m.h"
#include "../lab.h"

namespace color::calc {
namespace internal {
template <typename T> constexpr auto calc_c_prime(const T a, const T b) {
  return math::sqrt(math::pow(a, 2) + math::pow(b, 2));
}

template <typename T, typename Wp>
constexpr T calc_a_prime(basic_lab<T, Wp> const &color, T const mid_c) {
  T a = color.a();
  return a +
         (a / T(2)) *
             (T(1) - math::sqrt(math::pow(mid_c, 7) /
                                (math::pow(mid_c, 7) + math::pow(T(25), 7))));
}

template <typename T> constexpr T calc_h_prime(const T a, const T b) {
  if (a == 0 && b == 0) {
    return T(0);
  }

  T atan = math::atan2(b, a); // [-pi ; pi]

  if (atan >= T(0)) { // >= 180 or >= 360?
    return math::rad_to_deg(atan);
  }
  return math::rad_to_deg(atan) + T(360); // or 180?
}
} // namespace internal

template <std::floating_point T, typename Wp>
constexpr T cie_delta_e00(basic_lab<T, Wp> const &color1,
                          basic_lab<T, Wp> const &color2, T const &k_l = T(1),
                          T const &k_c = T(1), T const &k_h = T(1)) {
  T mid_l = (color1.l() + color2.l()) / T(2);
  T mid_c = (internal::calc_c_prime(color1.a(), color1.b()) +
             internal::calc_c_prime(color2.a(), color2.b())) /
            T(2);

  T a_1_prime = internal::calc_a_prime(color1, mid_c);
  T a_2_prime = internal::calc_a_prime(color2, mid_c);

  T c_1_prime = internal::calc_c_prime(a_1_prime, color1.b());
  T c_2_prime = internal::calc_c_prime(a_2_prime, color2.b());
  T mid_c_prime = (c_1_prime + c_2_prime) / T(2);
  T delta_c_prime = c_2_prime - c_1_prime;

  T h1_prime = internal::calc_h_prime(a_1_prime, color1.b());
  T h2_prime = internal::calc_h_prime(a_2_prime, color2.b());

  T delta_h_prime = 0;
  {
    T delta = h2_prime - h1_prime;

    if (math::abs(delta) <= T(180)) {
      delta_h_prime = delta;
    } else if (delta > T(180)) {
      delta_h_prime = delta - T(360);
    } else {
      delta_h_prime = delta + T(360);
    }
  }
  T delta_H_prime = T(2) * math::sqrt(c_1_prime * c_2_prime) *
                    math::sin(math::deg_to_rad(delta_h_prime / T(2)));
  T mid_h_prime = 0;
  {
    T delta = h1_prime - h2_prime;
    T delta_a = h1_prime + h2_prime;

    if (math::abs(delta) <= T(180)) {
      mid_h_prime = delta_a / T(2);
    } else if (math::abs(delta) > T(180) && h1_prime + h2_prime < T(360)) {
      mid_h_prime = (delta_a + T(360)) / T(2);
    } else {
      mid_h_prime = (delta_a - T(360)) / T(2);
    }
  }

  T t = T(1) - T(.17) * (math::cos(math::deg_to_rad(mid_h_prime - T(30)))) +
        T(0.24) * (math::cos(math::deg_to_rad(T(2) * mid_h_prime))) +
        T(0.32) * math::cos(math::deg_to_rad(T(3) * mid_h_prime + T(6))) -
        T(0.20) * math::cos(math::deg_to_rad(T(4) * mid_h_prime - T(63)));
  T s_l = T(1) + ((T(0.015) * math::pow((mid_l - T(50)), 2)) /
                  math::sqrt(T(20) + math::pow(mid_l - T(50), 2)));
  T s_c = T(1) + T(0.045) * mid_c_prime;
  T s_h = T(1) + T(0.015) * mid_c_prime * t;
  T r_t =
      T(-2) *
      math::sqrt(math::pow(mid_c_prime, 7) /
                 (math::pow(mid_c_prime, 7) + math::pow(T(25), 7))) *
      math::sin(math::deg_to_rad(
          T(60) * math::exp(-math::pow((mid_h_prime - T(275)) / T(25), 2))));
  T delta_l_prime = color2.l() - color1.l();

  // return math::sqrt(
  //     math::pow(delta_l_prime / (k_l * s_l), 2) +
  //     math::pow(delta_c_prime / (k_c * s_c), 2) +
  //     math::pow(delta_H_prime / (k_h * s_h), 2) +
  //     r_t * (delta_H_prime / (k_h * s_h) * (delta_c_prime / (k_c * s_c))));

  T final_c = delta_c_prime / (k_c * s_c);
  T final_h = delta_H_prime / (k_h * s_h);

  return math::sqrt((math::pow(delta_l_prime / (k_l * s_l), 2) +
                     math::pow(final_c, 2) + math::pow(final_h, 2) +
                     (r_t * final_c * final_h)));
}
} // namespace color::calc
