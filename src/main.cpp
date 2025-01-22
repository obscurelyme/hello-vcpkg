#include <fmt/core.h>
#include <raylib.h>

#include <Logging/core.hpp>

const int MAX_FRAMERATE = 60;

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  Zero::InitLogSinks();
  SetTraceLogCallback(Zero::RaylibTraceCallback);
  InitWindow(screenWidth, screenHeight, "Basic Window");
  SetTargetFPS(MAX_FRAMERATE);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congratz!", 190, 200, 20, BLACK);  // NOLINT
    EndDrawing();
  }

  CloseWindow();
  Zero::CleanLogSinks();

  return 0;
}