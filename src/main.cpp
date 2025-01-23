#include <fmt/core.h>
#include <raylib.h>

#include <Logging/core.hpp>

#include "errors/errors.h"

const int MAX_FRAMERATE = 60;

void CleanUp() {
  CloseWindow();
  Zero::CleanTraceLogSinks();
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  Zero::InitTraceLogSinks();
  SetTraceLogCallback(Zero::RaylibTraceCallback);

  InitWindow(screenWidth, screenHeight, "Basic Window");
  if (!IsWindowReady()) {
    Zero::ConsoleCrit("Raylib window was not initialized.");
    Zero::CleanTraceLogSinks();
    return Zero::Error::NoWindow;
  }

  SetTargetFPS(MAX_FRAMERATE);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congratz!", 190, 200, 20, BLACK);  // NOLINT
    EndDrawing();
  }

  CleanUp();

  return 0;
}