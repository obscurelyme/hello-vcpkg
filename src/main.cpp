#include <fmt/core.h>
#include <raylib.h>

#include <Logging/core.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

#include "args/args.h"
#include "errors/errors.h"
#include "monitors/monitors.h"
#include "textures/textures.h"

void CleanUp() {
  CloseWindow();
  Zero::CleanTraceLogSinks();
}

int main(int argc, char* argv[]) {
  try {
    Zero::Args program{argc, argv};
    if (program.help()) {
      program.showHelp();
      return 0;
    }

    const int screenWidth = program.screenWidth();
    const int screenHeight = program.screenHeight();
    const bool vsync = program.vsync();
    const bool fullscreen = program.fullscreen();

    Zero::MonitorsManager::toggleVsync(vsync);
    Zero::InitTraceLogSinks();
    SetTraceLogCallback(Zero::RaylibTraceCallback);
    InitWindow(screenWidth, screenHeight, "Raylib Window");
    if (!IsWindowReady()) {
      Zero::ConsoleCrit("Raylib window was not initialized.");
      Zero::CleanTraceLogSinks();  // NOTE: Do not call CloseWindow because there is no window to close
      return Zero::Error::NoWindow;
    }
    if (fullscreen) {
      Zero::MonitorsManager::toggleFullscreen();
    }

    Zero::Texture2D spaceship{"spaceship.png"};
    float deltaTime = 0.0f;

    while (!WindowShouldClose()) {
      deltaTime = GetFrameTime();

      // NOTE: input...
      spaceship.position.x += 100.0f * deltaTime;
      if (spaceship.position.x >= screenWidth) {
        spaceship.position.x = 0 - spaceship.get().width;
      }

      // NOTE: rendering...
      BeginDrawing();
      ClearBackground(BLACK);
      DrawFPS(0, 0);

      spaceship.draw();

      EndDrawing();
    }

    CleanUp();

    return 0;
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    return 1;
  }
}