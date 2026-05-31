#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "colorlib/generic_rgb.h"

namespace cli {
struct Cli {
  std::optional<color::standard_rgb<std::uint8_t>>
      color; // optional for support stdin
  bool benchmark;
  bool debug;
};

int cli_parse(Cli **opts, int argc, char *argv[],
              std::string *from_stdin); // bad pattern, I know
} // namespace cli
