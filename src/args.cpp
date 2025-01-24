#include "args/args.h"

Zero::Args::Args(const int argc, char* argv[]) : args(argparse::ArgumentParser{"Zero", "1.0.0"}) {
  this->args.add_argument("--width")
      .help("Sets the width of the window")
      .default_value(1920)
      .nargs(1)
      .action([](const std::string& value) -> int { return std::stoi(value); });

  this->args.add_argument("--height")
      .help("Sets the height of the window")
      .default_value(1080)
      .nargs(1)
      .action([](const std::string& value) -> int { return std::stoi(value); });

  this->args.add_argument("--vsync").help("Toggles vsync for the window").flag();

#if ZERO_BUILD == Debug
  this->args.add_argument("--fullscreen").help("Toggles fullscreen for the window").flag();
  this->args.add_argument("--verbose").help("Toggles verbose logging").flag();
#elif ZERO_BUILD == Release
#endif

  args.parse_args(argc, argv);
}