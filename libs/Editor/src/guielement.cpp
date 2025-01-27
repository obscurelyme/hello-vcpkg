#include "Editor/guielement.h"

namespace Zero {
  GuiElement::GuiElement() : node(YGNodeNew()) {}

  GuiElement::~GuiElement() { YGNodeFree(node); }

  void GuiElement::drawChildren() {
    for (size_t i = 0; i < YGNodeGetChildCount(node); i++) {
      auto childNode = YGNodeGetChild(node, i);
      GuiElement* child = static_cast<GuiElement*>(YGNodeGetContext(childNode));
      child->draw();
    }
  }

  void GuiElement::setFlexStyles(const Flex& flexStyles) {
    YGNodeStyleSetFlexDirection(node, flexStyles.flexDirection);
    YGNodeStyleSetAlignItems(node, flexStyles.flexAlign);
    YGNodeStyleSetJustifyContent(node, flexStyles.flexJustify);
  }

  void GuiElement::draw() { drawChildren(); }

  void GuiElement::setWidth(float width) { YGNodeStyleSetWidth(node, width); }
  void GuiElement::setHeight(float height) { YGNodeStyleSetHeight(node, height); }

  float GuiElement::getWidth() { return YGNodeLayoutGetWidth(node); }
  float GuiElement::getHeight() { return YGNodeLayoutGetHeight(node); }
  float GuiElement::getTop() { return YGNodeLayoutGetTop(node); }
  float GuiElement::getLeft() { return YGNodeLayoutGetLeft(node); }

  void GuiElement::addChild(GuiElement* element) { YGNodeInsertChild(node, element->node, YGNodeGetChildCount(node)); }
  void GuiElement::removeChild(GuiElement* element) { YGNodeRemoveChild(node, element->node); }
}  // namespace Zero