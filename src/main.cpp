#include <fmt/core.h>
#include <raylib.h>
#include <stdio.h>  // NOLINT

#include <ctime>
#include <string>

const int MAX_FRAMERATE = 60;
const int MAX_STRING_BUFFER = 256;

std::string FormatLogString(const char *format, va_list args) {
  char buffer[MAX_STRING_BUFFER];  // NOLINT

  const int stringLength = vsnprintf((char *)buffer, sizeof buffer, format, args);

  if (stringLength > sizeof buffer) {
    // TODO: we have a problem when the string is too big, figure this out later.
    fmt::println("[ERROR]: Buffer overflow detected formatting string from raylib. String will be truncated");
  }

  return std::string{buffer};  // NOLINT
}

// TODO: Leverage custom logs for the application as well.
void CustomLog(int logLevel, const char *text, va_list args) {
  const std::time_t result = std::time(nullptr);
  std::string timeString{std::asctime(std::localtime(&result))};

  switch (logLevel) {
    case LOG_INFO: {
      const std::string fmtString = FormatLogString(text, args);
      fmt::println("[INFO {1}]: {0}", fmtString, timeString);
      break;
    }
    case LOG_WARNING: {
      const std::string fmtString = FormatLogString(text, args);
      fmt::println("[WARN]: {}", fmtString);
      break;
    }
    case LOG_ERROR: {
      const std::string fmtString = FormatLogString(text, args);
      fmt::println("[ERROR]: {}", fmtString);
      break;
    }
    case LOG_DEBUG: {
      const std::string fmtString = FormatLogString(text, args);
      fmt::println("[DEBUG]: {}", fmtString);
      break;
    }
    default:
      break;
  }
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetTraceLogCallback(CustomLog);
  InitWindow(screenWidth, screenHeight, "Basic Window");
  SetTargetFPS(MAX_FRAMERATE);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congratz!", 190, 200, 20, BLACK);  // NOLINT
    EndDrawing();
  }

  CloseWindow();
  return 0;
}