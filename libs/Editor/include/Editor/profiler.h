#ifndef ZERO_EDITOR_PROFILER_H
#define ZERO_EDITOR_PROFILER_H

#include <chrono>
#include <string>
#include <unordered_map>
#include <utility>

namespace Zero {

  class Profiler {
    public:
      static void start(const std::string& name);
      static void pause(const std::string& name);
      static void unpause(const std::string& name);
      static void end(const std::string& name);
      static void print();

    private:
      static std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> startTimes;
      static std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> pauseStartTimes;
      static std::unordered_map<std::string, double> pauseTimes;
      static std::unordered_map<std::string, std::pair<double, double>> durations;
      static std::unordered_map<std::string, int> callCounts;
      static float currentTime;
      static float printTime;
  };

}  // namespace Zero

#endif