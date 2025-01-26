#include <fmt/core.h>
#include <fmt/format.h>
#include <raylib.h>
#include <raymath.h>

#include <Logging/core.hpp>
#include <entt/entity/fwd.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

#include "args/args.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "errors/errors.h"
#include "monitors/monitors.h"
#include "scene/scene.h"

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

    auto scene = Zero::CreateNewScene();
    Zero::SetActiveScene(scene);
    entt::entity entity = scene->createEntity();
    scene->entityRegistry.emplace<Zero::Sprite>(entity, "spaceship.png");
    scene->entityRegistry.emplace<Zero::Transform2D>(entity);
    auto& transform = scene->entityRegistry.get<Zero::Transform2D>(entity);

    float deltaTime = 0.0f;
    float fixedDeltaTime = 0.0f;
    // 60 FPS fixed delta time
    float fixedTargetDeltaTime = 1.0f / 60.0f;
    Zero::ConsoleTrace(fmt::format(fmt::runtime("Physics fixed timestep set to: {:f}"), fixedTargetDeltaTime));

    while (!WindowShouldClose()) {
      deltaTime = GetFrameTime();
      fixedDeltaTime += deltaTime;

      // NOTE: Process new entity inits for the active scene
      Zero::ProcessInits();
      // NOTE: Process new entity readys for the active scene
      Zero::ProcessReadies();

      // NOTE: Process updates for the active scene
      Zero::ProcessUpdates(deltaTime);
      transform.position.x += 200 * deltaTime;

      // NOTE: Process physics updates for the active scene if fixed timestep has passed
      fixedDeltaTime = Zero::ProcessPhysicsUpdates(fixedDeltaTime, fixedTargetDeltaTime);

      // NOTE: rendering...
      BeginDrawing();
      ClearBackground(BLACK);
      DrawFPS(0, 0);

      // NOTE: Process renders for the active scene
      Zero::Render();

      EndDrawing();

      // NOTE: Process destroys for the active scene
      Zero::ProcessDestroys();
    }

    scene.reset();
    Zero::SetActiveScene(nullptr);
    CleanUp();

    return 0;
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    return 1;
  }
}