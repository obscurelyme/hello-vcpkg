#include <fmt/core.h>
#include <raylib.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <Logging/core.hpp>
#include <string>

namespace Zero {
  const int MAX_STRING_BUFFER = 256;
  const int BASE_YEAR = 1900;
  const int OFFSET_ONE = 1;
  std::unique_ptr<TraceLogSinks> Sinks;
}  // namespace Zero

std::string Zero::FormatTraceLogMessage(const char *format, va_list args) {
  char buffer[MAX_STRING_BUFFER];

  const int stringLength = vsnprintf((char *)buffer, sizeof buffer, format, args);

  if ((unsigned long long)stringLength > sizeof buffer) {
    // TODO: we have a problem when the string is too big, figure this out later.
    fmt::println("[ERROR]: Buffer overflow detected formatting string from raylib. String will be truncated");
  }

  return std::string{std::addressof(buffer[0])};
}

void Zero::RaylibTraceCallback(int logLevel, const char *text, va_list args) {
  const std::string fmtString = FormatTraceLogMessage(text, args);

  switch (logLevel) {
    case LOG_TRACE: {
      Sinks->Console->trace("{:s}", fmtString);
      break;
    }
    case LOG_INFO: {
      Sinks->Console->info("{:s}", fmtString);
      break;
    }
    case LOG_WARNING: {
      Sinks->Console->warn("{:s}", fmtString);
      break;
    }
    case LOG_ERROR: {
      Sinks->Console->error("{:s}", fmtString);
      break;
    }
    case LOG_DEBUG: {
      Sinks->Console->debug("{:s}", fmtString);
      break;
    }
    case LOG_FATAL: {
      Sinks->Console->critical("{:s}", fmtString);
      break;
    }
    default:
      break;
  }
}

void handleSpdLogError(const std::string &msg) {
  Zero::Sinks->Console->error("Invalid message triggered an error: {} THIS IS NOT AN ERROR FROM YOUR APPLICATION.",
                              msg);
}

void Zero::InitTraceLogSinks() {
  Sinks = std::make_unique<TraceLogSinks>();
  Sinks->Console = spdlog::stdout_color_st("console");
  Sinks->Err = spdlog::stderr_color_st("stderr");
  Sinks->Console->set_level(spdlog::level::trace);
  Sinks->Console->set_error_handler(handleSpdLogError);
}

void Zero::CleanTraceLogSinks() { Sinks.reset(); }

void Zero::TraceLog(Zero::LogLevel logLevel, const std::string text, const std::vector<std::string> args) {
  if (logLevel == Zero::LogLevel::LOG_INFO) {
    Sinks->Console->info("{:s}", text);
  }

  if (logLevel == Zero::LogLevel::LOG_DEBUG) {
    Sinks->Console->debug("{:s}", text);
  }

  if (logLevel == Zero::LogLevel::LOG_TRACE) {
    Sinks->Console->trace("{:s}", text);
  }

  if (logLevel == Zero::LogLevel::LOG_WARNING) {
    Sinks->Console->warn("{:s}", text);
  }

  if (logLevel == Zero::LogLevel::LOG_ERROR) {
    Sinks->Console->error("{:s}", text);
  }

  if (logLevel == Zero::LogLevel::LOG_FATAL) {
    Sinks->Console->critical("{:s}", text);
  }
}