#include "editor/gui/gui.h"

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "Logging/core.hpp"

namespace Zero {
  void GuiElement::draw() {
    if (onDraw != nullptr) {
      onDraw();
    }
  }

  Editor::Editor() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, ColorToInt({77, 108, 146, 150}));

    ConsoleTrace("EDITOR: GUI initialized");
  }

  Editor::~Editor() {}

  void Editor::toggle() {
    if (GuiGetState() == STATE_DISABLED) {
      GuiEnable();
      enabled = true;
    } else {
      GuiDisable();
      enabled = false;
    }
  }

  void Editor::draw() {
    if (!enabled) {
      return;
    }

    GuiElement panel;
    panel.onDraw = []() {
      GuiPanel(Rectangle{0, 0, (float)GetScreenWidth(), 35}, "Zero Engine");
      DrawFPS((GetScreenWidth() - 100), 25);

      GuiPanel(Rectangle{0, 60, 300, (float)(GetScreenHeight() - 60)}, "Scene");
      GuiPanel(Rectangle{(float)(GetScreenWidth() - 300), 60, 300, (float)(GetScreenHeight() - 60)}, "Inspector");
    };
    panel.draw();

    // GuiPanel(Rectangle{50, 50, 200, 200}, "Panel");
    // GuiGroupBox(Rectangle{10, 10, 200, 200}, "Scene");
    // GuiGroupBox(Rectangle{10, 220, 200, 200}, "Inspector");
  }

  void Editor::setScene(Scene *scene) { this->scene = scene; }
}  // namespace Zero