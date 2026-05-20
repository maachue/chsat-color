#pragma once

#include <type_traits>
namespace color::wp {
struct D65 {};
struct D50 {};
struct D55 {};
struct D60 {};
struct D75 {};

template <typename T> struct is_wp : std::false_type {};
template <> struct is_wp<D65> : std::true_type {};
template <> struct is_wp<D50> : std::true_type {};
template <> struct is_wp<D55> : std::true_type {};
template <> struct is_wp<D60> : std::true_type {};
template <> struct is_wp<D75> : std::true_type {};

template <typename T>
concept wpoint = is_wp<T>::value;
} // namespace color::wp