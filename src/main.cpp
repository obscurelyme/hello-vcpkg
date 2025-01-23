#include <fmt/core.h>
#include <raylib.h>

#include <Logging/core.hpp>

#include "errors/errors.h"

const int MAX_FRAMERATE = 60;

void CleanUp() {
  CloseWindow();
  Zero::CleanTraceLogSinks();
}

Color darkred{.r = 131, .g = 0, .b = 9, .a = 255};
std::vector<Vector2> cachedMousePositions{};
Vector2 currentVec2;

int main() {
  const int screenWidth = 1920;
  const int screenHeight = 1080;

  Zero::InitTraceLogSinks();
  SetTraceLogCallback(Zero::RaylibTraceCallback);

  InitWindow(screenWidth, screenHeight, "Basic Window");
  if (!IsWindowReady()) {
    Zero::ConsoleCrit("Raylib window was not initialized.");
    Zero::CleanTraceLogSinks();  // NOTE: Do not call CloseWindow because there is no window to close
    return Zero::Error::NoWindow;
  }

  SetTargetFPS(MAX_FRAMERATE);

  while (!WindowShouldClose()) {
    // NOTE: input...
    currentVec2 = GetMousePosition();
    cachedMousePositions.push_back(currentVec2);

    // NOTE: rendering...
    BeginDrawing();
    ClearBackground(BLACK);

    for (const Vector2& vec2 : cachedMousePositions) {
      DrawPixel(vec2.x, vec2.y, RED);
    }

    DrawLineEx(Vector2{0, 0}, Vector2{500, 500}, 10.0f, darkred);

    EndDrawing();
  }

  CleanUp();

  return 0;
}