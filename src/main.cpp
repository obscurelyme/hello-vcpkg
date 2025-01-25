#include <fmt/core.h>
#include <raylib.h>
#include <raymath.h>

#include <Logging/core.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "args/args.h"
#include "ecs/ecs.h"
#include "errors/errors.h"
#include "game/entities/player.h"
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
    SetExitKey(KeyboardKey::KEY_ESCAPE);
    if (fullscreen) {
      Zero::MonitorsManager::toggleFullscreen();
    }

    Zero::EntityManager::Create();
    float deltaTime = 0.0f;

    Zero::Player* player = new Zero::Player();
    player->init();

    while (!WindowShouldClose()) {
      deltaTime = GetFrameTime();

      // TODO: Process new entity inits
      // TODO: Process new entity readys

      // NOTE: Process updates
      for (auto it = Zero::entities.begin(); it != Zero::entities.end(); ++it) {
        it->second->update(deltaTime);
      }

      // NOTE: Physics updates
      for (auto it = Zero::entities.begin(); it != Zero::entities.end(); ++it) {
        it->second->physicsUpdate();
      }

      // NOTE: rendering...
      BeginDrawing();
      ClearBackground(BLACK);
      DrawFPS(0, 0);

      Zero::EntityManager::Render();

      EndDrawing();
    }

    delete player;
    Zero::EntityManager::Destroy();
    CleanUp();

    return 0;
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    return 1;
  }
}