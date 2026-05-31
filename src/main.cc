#ifdef __unix__
#include <unistd.h>
#endif

#include <iostream>
#include <string>

#include <fmt/printf.h>
#include <fmt/ranges.h>

#include "colorlib.h"

#include "cli.h"

int main(int argc, char *argv[]) {
  std::string from_stdin{};

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

#ifdef __unix__
  if (!isatty(STDIN_FILENO)) {
    std::cin >> from_stdin; // only one word
  }
#endif

  cli::Cli cli{};
  {
    auto *from_stdin_ = from_stdin.empty() ? nullptr : &from_stdin;
    auto *is_valid = &cli;
    auto return_code = cli::cli_parse(&is_valid, argc, argv, from_stdin_);

    if (is_valid == nullptr) {
      if (return_code != 0) {
      }

      return return_code;
    }
  }

  return 0;
}
