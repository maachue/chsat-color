#ifdef __unix__
#include <unistd.h>
#endif

#include <fmt/printf.h>
#include <fmt/ranges.h>

#include "colorlib.h"

#include "cli.h"

int main(int argc, char *argv[]) {
#ifdef __unix__
  if (!isatty(STDIN_FILENO)) {
    // piped
  }
#endif

  cli::Cli cli{};
  {
    auto *is_valid = &cli;
    auto test = std::string_view("#ffff");
    auto return_code = cli::cli_parse(&is_valid, argc, argv, &test);

    if (is_valid == nullptr) {
      if (return_code != 0) {
      }

      return return_code;
    }
  }

  return 0;
}
