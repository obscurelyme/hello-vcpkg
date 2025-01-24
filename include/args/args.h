#ifndef ZERO_ARGS_H_
#define ZERO_ARGS_H_

#include <argparse/argparse.hpp>
#include <iostream>
#include <string_view>

namespace Zero {
  /**
   * Argument manager for the application.
   */
  class Args {
    public:
      Args() = delete;
      Args(const int argc, char* argv[]);
      Args(const Args&) = delete;
      Args& operator=(const Args&) = delete;
      // Returns the value of an arg passed into the program.
      template <typename T>
      T get(std::string_view arg) const {
        return this->args.get<T>(arg);
      };
      void showHelp() const { std::cout << this->args << std::endl; }
      std::string version() const { return this->args.get<std::string>("version"); }
      bool help() const { return this->args.get<bool>("help"); }
      bool vsync() const { return this->args.get<bool>("vsync"); }
      bool fullscreen() const {
#if ZERO_BUILD == Debug
        return this->args.get<bool>("fullscreen");
#else
        // NOTE: force fullscreen mode on Release builds
        return true;
#endif
      }
      int screenWidth() const { return this->args.get<int>("width"); }
      int screenHeight() const { return this->args.get<int>("height"); }

    private:
      argparse::ArgumentParser args;
  };
}  // namespace Zero

#endif
