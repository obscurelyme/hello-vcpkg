#include "Editor/guiroot.h"

namespace Zero {
  GuiRoot::GuiRoot() {
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
    YGNodeCalculateLayout(node, GetScreenWidth(), GetScreenHeight(), YGDirectionLTR);
    // Draw the nodes
    drawChildren();
  }
}  // namespace Zero