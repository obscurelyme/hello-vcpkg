#include <fmt/core.h>
#include <raylib.h>

#include <Logging/core.hpp>
#include <algorithm>
#include <filesystem>

#include "errors/errors.h"
#include "textures/textures.h"

const int MAX_FRAMERATE = 60;

void CleanUp() {
  CloseWindow();
  Zero::CleanTraceLogSinks();
}

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
  Zero::Texture2D spaceship{"spaceship.png"};

  while (!WindowShouldClose()) {
    // NOTE: input...

    // NOTE: rendering...
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(spaceship.get(), 0, 0, WHITE);

    EndDrawing();
  }

  CleanUp();

  return 0;
}