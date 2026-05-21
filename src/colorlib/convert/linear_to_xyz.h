#pragma once

#include <concepts>

#include "../chsat_m.h"
#include "../convert.h"

#include "../generic_rgb.h"
#include "../xyz.h"

namespace color {
namespace matrix {
template <std::floating_point T>
constexpr math::matrix3x3<T> linear_xyz_d65 = {
    {{T(0.4124564), T(0.3575761), T(0.1804375)},
     {T(0.2126729), T(0.7151522), T(0.0721750)},
     {T(0.0193339), T(0.1191920), T(0.9503041)}}};
}

template <std::floating_point T> struct converter<linear_rgb<T>, xyzd65<T>> {
  constexpr static xyzd65<T> convert(linear_rgb<T> const &from) {
    return xyzd65<T>{
        math::vec_multiply_matrix(from.data, matrix::linear_xyz_d65<T>)};
  }
};
} // namespace color
