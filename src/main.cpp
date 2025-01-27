#include <Editor/core.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <imgui.h>
#include <raylib.h>
#include <raymath.h>

#include <Logging/core.hpp>
#include <entt/entity/fwd.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Editor/types.h"
#include "args/args.h"
#include "ecs/components/nativescript.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"
#include "ecs/entity.h"
#include "errors/errors.h"
#include "game/entities/player.h"
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
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
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

    Zero::Entity player = scene->createEntity();
    player.addComponent<Zero::Sprite>("spaceship.png");
    player.addComponent<Zero::Transform2D>();
    player.addComponent<Zero::NativeScript>().bind<Zero::Player>();

    float deltaTime = 0.0f;
    float fixedDeltaTime = 0.0f;
    // 60 FPS fixed delta time
    float fixedTargetDeltaTime = 1.0f / 60.0f;
    Zero::ConsoleTrace(fmt::format(fmt::runtime("Physics fixed timestep set to: {:f}"), fixedTargetDeltaTime));

    Zero::Editor editor;
    Zero::GuiPanel panel1{"Test Panel #1"};
    Zero::GuiPanel panel2{"Test Panel #2"};
    Zero::GuiPanel panel3{"Test Panel #3"};

    Zero::GuiViewInput viewInput{true, true, 100, 100};
    Zero::GuiView view{viewInput};
    Zero::Flex flexStyles{.flexDirection = Zero::FlexDirection::YGFlexDirectionColumn,
                          .flexAlign = Zero::FlexAlign::YGAlignCenter,
                          .flexJustify = Zero::FlexJustify::YGJustifyCenter};
    view.setFlexStyles(flexStyles);

    panel1.setHeight(500);
    panel1.setWidth(200);
    Zero::Margin margin{.left = 10};
    panel1.setMargin(margin);

    editor.root.addChild(&panel2);
    editor.root.addChild(&panel1);
    editor.root.addChild(&view);
    view.addChild(&panel3);

    // Zero::AppBar appBar{"Application"};

    while (!WindowShouldClose()) {
      deltaTime = GetFrameTime();
      fixedDeltaTime += deltaTime;

      // NOTE: Process new entity inits for the active scene
      Zero::ProcessInits();
      // NOTE: Process new entity readys for the active scene
      Zero::ProcessReadies();

      // NOTE: Process updates for the active scene
      Zero::ProcessUpdates(deltaTime);

      // NOTE: Process physics updates for the active scene if fixed timestep has passed
      fixedDeltaTime = Zero::ProcessPhysicsUpdates(fixedDeltaTime, fixedTargetDeltaTime);

      // NOTE: rendering...
      BeginDrawing();
      ClearBackground(Zero::Background);
      DrawFPS(0, 0);

      // NOTE: Process renders for the active scene
      Zero::Render();

      editor.beginRender();
      editor.render();
      editor.endRender();

      EndDrawing();

      // NOTE: Process destroys for the active scene
      Zero::ProcessDestroys();
    }

    editor.cleanUp();
    scene.reset();
    Zero::SetActiveScene(nullptr);
    CleanUp();

    return 0;
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    return 1;
  }
}