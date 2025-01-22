#ifndef ZERO_LOGGING_H_
#define ZERO_LOGGING_H_

#define SPDLOG_COMPILED_LIB  // NOLINT
#define SPDLOG_FMT_EXTERNAL  // NOLINT
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <string>
#include <vector>

namespace Zero {
  enum class LogLevel {
    LOG_ALL = 100,  // Display all logs
    LOG_TRACE,      // Trace logging, intended for internal use only
    LOG_DEBUG,      // Debug logging, used for internal debugging, it should be disabled on release builds
    LOG_INFO,       // Info logging, used for program execution info
    LOG_WARNING,    // Warning logging, used on recoverable failures
    LOG_ERROR,      // Error logging, used on unrecoverable failures
    LOG_FATAL,      // Fatal logging, used to abort program: exit(EXIT_FAILURE)
    LOG_NONE        // Disable logging
  };

  struct LogSinks {
    std::shared_ptr<spdlog::logger> Console;
    std::shared_ptr<spdlog::logger> Err;
  };

  void InitLogSinks();
  void CleanLogSinks();

  /**
   * Formats a log message from Raylib and returns it as a std::string
   */
  std::string FormatLogMessage(const char *format, va_list args);

  /**
   * Callback function meant to be passed to Raylib's `SetTraceLogCallback` function.
   * This function will handle parsing Raylib's traces and forwards them to
   * the correct sinks.
   */
  void RaylibTraceCallback(int logLevel, const char *text, va_list args);

  void Log(LogLevel logLevel, const std::string text, const std::vector<std::string> args);
}  // namespace Zero

#endif