#include <fmt/printf.h>
#include <fmt/ranges.h>

#include "colorlib.h"
#include "colorlib/convert/xyz_to_lab.h"

int main() {
  constexpr auto color = color::from_u8<double>(255, 255, 225);
  constexpr auto lcolor = color::convert<color::linear_rgb<double>>(color);
  constexpr auto convert = color::convert<color::xyzd65<double>>(lcolor);
  constexpr auto caonvert = color::convert<color::labd65<double>>(convert);

  fmt::println("{}", color.data);
  fmt::println("{}", lcolor.data);
  fmt::println("{}", convert.data);
  fmt::println("{}", caonvert.data);

  return 0;
}
