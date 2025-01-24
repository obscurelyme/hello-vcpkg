#ifndef ZERO_LOGGING_H_
#define ZERO_LOGGING_H_

#include <memory>
#include <string>
#include <vector>

namespace spdlog {
  class logger;
}

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

  struct TraceLogSinks {
    std::shared_ptr<spdlog::logger> Console;
  };

  void InitTraceLogSinks();
  void CleanTraceLogSinks();

  /**
   * Formats a log message from Raylib and returns it as a std::string
   */
  std::string FormatTraceLogMessage(const char *format, va_list args);

  /**
   * Callback function meant to be passed to Raylib's `SetTraceLogCallback` function.
   * This function will handle parsing Raylib's traces and forwards them to
   * the correct sinks.
   */
  void RaylibTraceCallback(int logLevel, const char *text, va_list args);

  void TraceLog(LogLevel logLevel, const std::string &text, const std::vector<std::string> args);

  // Logs an [info] statement to the console.
  void ConsoleLog(const std::string &text);

  // Logs a [warn] statement to the console.
  void ConsoleWarn(const std::string &text);

  // Logs an [error] statement to the console.
  void ConsoleErr(const std::string &text);

  // Logs a [critial] statement to the console.
  void ConsoleCrit(const std::string &text);

  // Logs a [debug] statement to the console.
  void ConsoleDebug(const std::string &text);
}  // namespace Zero

#endif