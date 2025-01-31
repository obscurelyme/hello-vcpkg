#include "Editor/guiroot.h"

#include <YGConfig.h>
#include <YGValue.h>

#include "Editor/profiler.h"

namespace Zero {
  GuiRoot::GuiRoot() {
    type = Elements::View;
    // Set the root node to the size of the screen
    YGNodeStyleSetFlexDirection(node, YGFlexDirectionRow);
    YGNodeStyleSetWidth(node, GetScreenWidth());
    YGNodeStyleSetHeight(node, GetScreenHeight());
  }

  void GuiRoot::draw() {
    // Set the root node to the size of the screen
    YGNodeStyleSetWidth(node, GetScreenWidth());
    YGNodeStyleSetHeight(node, GetScreenHeight());
    // Calculate the layout for the items
    if (YGNodeGetHasNewLayout(node)) {
      YGNodeCalculateLayout(node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR);
    }

    // Draw the nodes
    drawChildren();
  }
}  // namespace Zero