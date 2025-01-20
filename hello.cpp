#include <iostream>
#include <vector>
#include <string>
#include <fmt/core.h>
#include <raylib.h>

int main()
{
  fmt::println("Hello\n");

  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Basic Window");
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congratz!", 190, 200, 20, BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}