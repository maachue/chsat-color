#include "cli.h"

#include <cstdint>
#include <cstdio>
#include <string>
#include <string_view>

#include <fmt/base.h>
#include <fmt/format.h>

namespace cli {
constexpr std::string_view RED_BOLD = "\x1b[31;1m";
constexpr std::string_view BLUE_BOLD = "\x1b[34;1m";
constexpr std::string_view BOLD_UNDERLINE = "\x1b[1;4m";
constexpr std::string_view BOLD = "\x1b[1m";
constexpr std::string_view RESET = "\x1b[0m";
template <typename... T> void error(fmt::format_string<T...> fmt, T &&...args) {
  fmt::print(stdout, "{}error:{} ", RED_BOLD, RESET);
  fmt::vprintln(stdout, fmt.get(), fmt::make_format_args(args...));
  std::fflush(stdout);
}

template <typename... T> void note(fmt::format_string<T...> fmt, T &&...args) {
  fmt::print(stdout, "{}note:{} ", BLUE_BOLD, RESET);
  fmt::vprintln(stdout, fmt.get(), fmt::make_format_args(args...));
  std::fflush(stdout);
}

void show_help() {
  // clang-format off
  fmt::print("{1}Arguments:{0}\n"
             "  [COLOR]\n\n"
             "{1}Options:{0}\n"
             "  {2}    --benchmark{0}             Show how long to generate palette\n"
             "  {2}    --debug{0}                 Debug ({3}DO NOT USE{0})\n"
             "  {2}-h, --help{0}                  Print help\n"
             "  {2}-v, --version{0}               Print version (more with double this option '{2}-vv{0}')\n", RESET, BOLD_UNDERLINE, BOLD, RED_BOLD);
  // clang-format on
}

int parse_position(std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> &result,
                   std::string_view str) {
  return 0;
}

int cli_parse(Cli **opts, int argc, char *argv[], std::string *from_stdin) {
  std::string_view position{};
  auto error_lambda = [&opts]<typename... T>(fmt::format_string<T...> fmt,
                                             T &&...args) {
    (*opts) = nullptr;
    error(fmt, std::forward<T>(args)...);
  };
  bool parse_position_only = false;

  for (int i = 1; i < argc; ++i) {
    std::string_view arg(argv[i]);

    if (arg == "-h" || arg == "--help") {
      show_help();
      return 0;
    }

    if (arg == "--") {
      parse_position_only = true;
      continue;
    }

    if (parse_position_only) {
      if (i != argc - 1 && argv[i + 1] != nullptr) {
        error_lambda("unexpected argument '{}'", std::string_view(argv[i + 1]));
        return 1;
      }

      position = arg;
      break;
    }

    if (arg.size() > 2 && arg.starts_with("--")) {
      continue;
    }

    if (arg.size() > 1 && arg[0] == '-') {
      continue;
    }

    // constructor default for std::string_view is nullptr
    if (position.data() == nullptr || position.size() == 0) {
      position = arg;
      continue;
    }

    error_lambda("unexpected argument '{}'", arg);
    return 1;
  }

  if (from_stdin != nullptr) {
    note("value '{}' piped!", *from_stdin);
  }

  if (position.empty()) {
    error_lambda("required argument {}[COLOR]{}", "\x1b[32;1m", RESET);
    note("A valid {}[COLOR]{} argument can be as '#fff', '#ffffff', 'fff', "
         "'ffffff' or '255,255,255' depend on your option.",
         "\x1b[32;1m", RESET);
    return 1;
  }

  return 0;
}
} // namespace cli
