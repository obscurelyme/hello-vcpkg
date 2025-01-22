#include <fmt/core.h>
#include <raylib.h>

#include <Logging/core.hpp>
#include <ctime>
#include <string>

namespace Zero {
  const int MAX_STRING_BUFFER = 256;
  const int BASE_YEAR = 1900;
  const int OFFSET_ONE = 1;
  LogSinks *Sinks;
}  // namespace Zero

std::string Zero::FormatLogMessage(const char *format, va_list args) {
  char buffer[MAX_STRING_BUFFER];

  const int stringLength = vsnprintf((char *)buffer, sizeof buffer, format, args);

  if ((unsigned long long)stringLength > sizeof buffer) {
    // TODO: we have a problem when the string is too big, figure this out later.
    fmt::println("[ERROR]: Buffer overflow detected formatting string from raylib. String will be truncated");
  }

  return std::string{std::addressof(buffer[0])};
}

void Zero::RaylibTraceCallback(int logLevel, const char *text, va_list args) {
  const std::time_t currentTime = std::time(nullptr);
  const tm *now = std::localtime(&currentTime);

  // const auto chronoNow = std::chrono::system_clock::now();
  // const auto duration = chronoNow.time_since_epoch();

  // std::string timeString = fmt::format(fmt::runtime("{:s}"), now);

  std::string timeString = fmt::format("({:d}-{:d}-{:d} {:d}:{:d}:{:d})", OFFSET_ONE + now->tm_mon, now->tm_mday,
                                       BASE_YEAR + now->tm_year, now->tm_hour, now->tm_min, now->tm_sec);
  const std::string fmtString = FormatLogMessage(text, args);

  switch (logLevel) {
    case LOG_INFO: {
      fmt::println("[INFO {1}]: {0}", fmtString, timeString);
      break;
    }
    case LOG_WARNING: {
      fmt::println("[WARN]: {}", fmtString);
      break;
    }
    case LOG_ERROR: {
      fmt::println("[ERROR]: {}", fmtString);
      break;
    }
    case LOG_DEBUG: {
      fmt::println("[DEBUG]: {}", fmtString);
      break;
    }
    default:
      break;
  }
}

void Zero::InitLogSinks() {
  Sinks = new LogSinks{};
  Sinks->Console = spdlog::stdout_color_st("console");
  Sinks->Err = spdlog::stderr_color_st("err");
}

void Zero::CleanLogSinks() { delete Sinks; }