#pragma once

#include <type_traits>

namespace color {

namespace internal {

template <typename From, typename To> struct color_cannot_convert_to;

template <typename From, typename To> struct converter_error {
  constexpr static auto convert(From const &)
      -> color_cannot_convert_to<From, To>;
};

template <typename From, typename To> struct converter_complete {
  constexpr static auto convert(From const &) -> To;
};

} // namespace internal

template <typename From, typename To, typename = void>
struct converter : internal::converter_error<From, To> {};

template <typename From, typename To>
struct converter<From, To, std::enable_if_t<std::is_convertible_v<From, To>>>
    : internal::converter_complete<From, To> {};

template <typename To, typename From>
constexpr auto convert(From const &color) {
  return converter<From, To>::convert(color);
}
} // namespace color