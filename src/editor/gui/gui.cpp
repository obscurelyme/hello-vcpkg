#include "editor/gui/gui.h"

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "Logging/core.hpp"

namespace Zero {
  Editor::Editor() {
    ConsoleTrace("Editor GUI initialized.");

    // GuiSetStyle(int control, int property, int value)
  }

  Editor::~Editor() {}
}  // namespace Zero