#include "Editor/profiler.h"

#include <fmt/base.h>
#include <fmt/printf.h>
#include <raylib.h>

#include <chrono>

namespace Zero {
  std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> Profiler::startTimes;
  std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> Profiler::pauseStartTimes;
  std::unordered_map<std::string, double> Profiler::pauseTimes;
  std::unordered_map<std::string, std::pair<double, double>> Profiler::durations{};
  std::unordered_map<std::string, int> Profiler::callCounts{};
  float Profiler::currentTime = 0.0f;
  float Profiler::printTime = 5.0f;

  void Profiler::start(const std::string& name) {
    startTimes[name] = std::chrono::high_resolution_clock::now();
    pauseTimes[name] = 0;
  }

  void Profiler::pause(const std::string& name) { pauseStartTimes[name] = std::chrono::high_resolution_clock::now(); }

  void Profiler::unpause(const std::string& name) {
    auto endPause = std::chrono::high_resolution_clock::now();
    auto startPause = pauseStartTimes[name];
    pauseTimes[name] += std::chrono::duration_cast<std::chrono::microseconds>(endPause - startPause).count() / 1000.0;
  }

  void Profiler::end(const std::string& name) {
    auto endTime = std::chrono::high_resolution_clock::now();
    auto startTime = startTimes[name];
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.0;
    durations[name].first += duration;
    durations[name].second = duration;
    callCounts[name]++;
  }

  void Profiler::print() {
    currentTime += GetFrameTime();

    if (currentTime >= printTime) {
      currentTime = 0.0f;
      fmt::println("--- Profiler Results --------------------------------------------");
      for (auto& [name, duration] : durations) {
        auto count = callCounts[name];
        auto pauseTime = pauseTimes[name];
        if (count > 0) {
          fmt::print("Profiler: {:s} took {:f}ms total over {:d} calls, and {:f}ms over this call.\n", name,
                     duration.first - pauseTime, count, duration.second);
        }
      }
      fmt::println("----------------------------------------------------------------");
    }
  }

}  // namespace Zero