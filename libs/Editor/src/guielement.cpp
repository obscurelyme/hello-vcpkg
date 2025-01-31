#include "Editor/guielement.h"

#include <YGNodeStyle.h>
#include <fmt/printf.h>

#include "Editor/types.h"

namespace Zero {
  GuiElement::GuiElement() : node(YGNodeNew()), title(""), id("") {}

  GuiElement::~GuiElement() {
    for (size_t i = 0; i < YGNodeGetChildCount(node); i++) {
      auto childNode = YGNodeGetChild(node, i);
      GuiElement* child = static_cast<GuiElement*>(YGNodeGetContext(childNode));
      delete child;
    }
    YGNodeFree(node);
  }

  void GuiElement::drawChildren() {
    for (size_t i = 0; i < YGNodeGetChildCount(node); i++) {
      auto childNode = YGNodeGetChild(node, i);
      GuiElement* child = static_cast<GuiElement*>(YGNodeGetContext(childNode));
      child->draw();
    }
  }

  void GuiElement::setFlexStyles(const Flex& flexStyles) {
    if (flexStyles.flex.has_value()) {
      YGNodeStyleSetFlex(node, flexStyles.flex.value());
    }

    if (flexStyles.flexAlign.has_value()) {
      YGNodeStyleSetAlignItems(node, flexStyles.flexAlign.value());
    }

    if (flexStyles.flexBasisAuto.has_value() && flexStyles.flexBasisAuto.value()) {
      YGNodeStyleSetFlexBasisAuto(node);
    }

    if (flexStyles.flexBasis.has_value()) {
      // NOTE: basis logic is more complex
      if (flexStyles.flexBasisAuto.has_value() && !flexStyles.flexBasisAuto.value()) {
        if (flexStyles.useFlexBasisPercent.has_value() && flexStyles.useFlexBasisPercent.value()) {
          YGNodeStyleSetFlexBasisPercent(node, flexStyles.flexBasis.value());
        } else {
          YGNodeStyleSetFlexBasis(node, flexStyles.flexBasis.value());
        }
      }
    }

    if (flexStyles.flexDirection.has_value()) {
      YGNodeStyleSetFlexDirection(node, flexStyles.flexDirection.value());
    }

    if (flexStyles.flexGrow.has_value()) {
      YGNodeStyleSetFlexGrow(node, flexStyles.flexGrow.value());
    }

    if (flexStyles.flexJustify.has_value()) {
      YGNodeStyleSetJustifyContent(node, flexStyles.flexJustify.value());
    }

    if (flexStyles.flexShrink.has_value()) {
      YGNodeStyleSetFlexShrink(node, flexStyles.flexShrink.value());
    }

    if (flexStyles.flexWrap.has_value()) {
      YGNodeStyleSetFlexWrap(node, flexStyles.flexWrap.value());
    }
  }

  void GuiElement::setStyles(const Styles& styles) {
    if (styles.height.has_value()) {
      if (styles.heightIsPercent.has_value() && styles.heightIsPercent.value()) {
        YGNodeStyleSetHeightPercent(node, styles.height.value());
      } else {
        YGNodeStyleSetHeight(node, styles.height.value());
      }
    }

    if (styles.width.has_value()) {
      if (styles.widthIsPercent.has_value() && styles.widthIsPercent.value()) {
        YGNodeStyleSetWidthPercent(node, styles.width.value());
      } else {
        YGNodeStyleSetWidth(node, styles.width.value());
      }
    }

    if (styles.maxHeight.has_value()) {
      if (styles.maxHeightIsPercent.has_value() && styles.maxHeightIsPercent.value()) {
        YGNodeStyleSetMaxHeightPercent(node, styles.maxHeight.value());
      } else {
        YGNodeStyleSetMaxHeight(node, styles.maxHeight.value());
      }
    }

    if (styles.maxWidth.has_value()) {
      if (styles.maxWidthIsPercent.has_value() && styles.maxWidthIsPercent.value()) {
        YGNodeStyleSetMaxWidthPercent(node, styles.maxWidth.value());
      } else {
        YGNodeStyleSetMaxWidth(node, styles.maxWidth.value());
      }
    }

    if (styles.minHeight.has_value()) {
      if (styles.minHeightIsPercent.has_value() && styles.minHeightIsPercent.value()) {
        YGNodeStyleSetMinHeightPercent(node, styles.minHeight.value());
      } else {
        YGNodeStyleSetMinHeight(node, styles.minHeight.value());
      }
    }

    if (styles.minWidth.has_value()) {
      if (styles.minWidthIsPercent.has_value() && styles.minWidthIsPercent.value()) {
        YGNodeStyleSetMinWidthPercent(node, styles.minWidth.value());
      } else {
        YGNodeStyleSetMinWidth(node, styles.minWidth.value());
      }
    }

    if (styles.border.has_value()) {
      setBorder(styles.border.value());
    }

    if (styles.margin.has_value()) {
      setMargin(styles.margin.value());
    }

    if (styles.padding.has_value()) {
      setPadding(styles.padding.value());
    }
  }

  void GuiElement::setBorder(const Border& border) {
    if (border.all.has_value()) {
      YGNodeStyleSetBorder(node, Edge::YGEdgeAll, border.all.value());
    }

    if (border.top.has_value()) {
      YGNodeStyleSetBorder(node, Edge::YGEdgeTop, border.top.value());
    }

    if (border.right.has_value()) {
      YGNodeStyleSetBorder(node, Edge::YGEdgeRight, border.right.value());
    }

    if (border.bottom.has_value()) {
      YGNodeStyleSetBorder(node, Edge::YGEdgeBottom, border.bottom.value());
    }

    if (border.left.has_value()) {
      YGNodeStyleSetBorder(node, Edge::YGEdgeLeft, border.left.value());
    }
  }

  void GuiElement::setMargin(const Margin& margin) {
    if (margin.all.has_value()) {
      YGNodeStyleSetMargin(node, Edge::YGEdgeAll, margin.all.value());
    }

    if (margin.top.has_value()) {
      YGNodeStyleSetMargin(node, Edge::YGEdgeTop, margin.top.value());
    }

    if (margin.right.has_value()) {
      YGNodeStyleSetMargin(node, Edge::YGEdgeRight, margin.right.value());
    }

    if (margin.bottom.has_value()) {
      YGNodeStyleSetMargin(node, Edge::YGEdgeBottom, margin.bottom.value());
    }

    if (margin.left.has_value()) {
      YGNodeStyleSetMargin(node, Edge::YGEdgeLeft, margin.left.value());
    }
  }

  void GuiElement::setPadding(const Padding& padding) {
    if (padding.all.has_value()) {
      YGNodeStyleSetPadding(node, Edge::YGEdgeAll, padding.all.value());
    }

    if (padding.top.has_value()) {
      YGNodeStyleSetPadding(node, Edge::YGEdgeTop, padding.top.value());
    }

    if (padding.right.has_value()) {
      YGNodeStyleSetPadding(node, Edge::YGEdgeRight, padding.right.value());
    }

    if (padding.bottom.has_value()) {
      YGNodeStyleSetPadding(node, Edge::YGEdgeBottom, padding.bottom.value());
    }

    if (padding.left.has_value()) {
      YGNodeStyleSetPadding(node, Edge::YGEdgeLeft, padding.left.value());
    }
  }

  void GuiElement::setGap(const Gap& gap) {
    if (gap.all.has_value()) {
      YGNodeStyleSetGap(node, YGGutter::YGGutterAll, gap.all.value());
    }

    if (gap.column.has_value()) {
      YGNodeStyleSetGap(node, YGGutter::YGGutterColumn, gap.column.value());
    }

    if (gap.row.has_value()) {
      YGNodeStyleSetGap(node, YGGutter::YGGutterRow, gap.row.value());
    }
  }

  void GuiElement::draw() {
    calculate();
    drawChildren();
  }

  void GuiElement::setWidth(float width, bool percent) {
    if (percent) {
      YGNodeStyleSetWidthPercent(node, width);
    } else {
      YGNodeStyleSetWidth(node, width);
    }
  }
  void GuiElement::setHeight(float height, bool percent) {
    if (percent) {
      YGNodeStyleSetHeightPercent(node, height);
    } else {
      YGNodeStyleSetHeight(node, height);
    }
  }

  float GuiElement::getWidth() { return YGNodeLayoutGetWidth(node); }
  float GuiElement::getHeight() { return YGNodeLayoutGetHeight(node); }
  float GuiElement::getTop() { return YGNodeLayoutGetTop(node); }
  float GuiElement::getLeft() { return YGNodeLayoutGetLeft(node); }

  void GuiElement::addChild(GuiElement* element) {
    YGNodeInsertChild(node, element->node, YGNodeGetChildCount(node));
    children.push_back(element);
    element->parent = this;
  }
  void GuiElement::removeChild(GuiElement* element) {
    YGNodeRemoveChild(node, element->node);
    children.erase(std::find(children.begin(), children.end(), element));
    element->parent = nullptr;
  }
  void GuiElement::setTitle(const std::string& t) {
    // NOTE: set the title
    title = t;
  }

  void GuiElement::calculate() {
    calculateBorder();
    calculateMargin();
    calculatePadding();
    calculateSize();
    calculatePosition();
  }

  void GuiElement::calculateSize() {
    calculatedSize.x = getWidth();
    calculatedSize.y = getHeight();
  }

  void GuiElement::calculatePosition() {
    auto parent = this->parent;
    if (parent) {
      calculatedPosition.x = getLeft() + parent->calculatedPosition.x + parent->margin.z;
      calculatedPosition.y = getTop() + parent->calculatedPosition.y + parent->margin.w;
      return;
    }
    calculatedPosition.x = getLeft();
    calculatedPosition.y = getTop();
  }

  void GuiElement::calculateBorder() {
    border =
        calculateVec4(YGNodeStyleGetBorder(node, Edge::YGEdgeAll), YGNodeStyleGetBorder(node, Edge::YGEdgeTop),
                      YGNodeStyleGetBorder(node, Edge::YGEdgeRight), YGNodeStyleGetBorder(node, Edge::YGEdgeBottom),
                      YGNodeStyleGetBorder(node, Edge::YGEdgeLeft));
  }

  void GuiElement::calculateMargin() {
    margin = calculateVec4(
        YGNodeStyleGetMargin(node, Edge::YGEdgeAll).value, YGNodeStyleGetMargin(node, Edge::YGEdgeTop).value,
        YGNodeStyleGetMargin(node, Edge::YGEdgeRight).value, YGNodeStyleGetMargin(node, Edge::YGEdgeBottom).value,
        YGNodeStyleGetMargin(node, Edge::YGEdgeLeft).value);
  }

  void GuiElement::calculatePadding() {
    padding = calculateVec4(
        YGNodeStyleGetPadding(node, Edge::YGEdgeAll).value, YGNodeStyleGetPadding(node, Edge::YGEdgeTop).value,
        YGNodeStyleGetPadding(node, Edge::YGEdgeRight).value, YGNodeStyleGetPadding(node, Edge::YGEdgeBottom).value,
        YGNodeStyleGetPadding(node, Edge::YGEdgeLeft).value);
  }

  Vector4 GuiElement::calculateVec4(const float all, const float top, const float right, const float bottom,
                                    const float left) {
    Vector4 vec4;

    vec4.w = YGFloatIsUndefined(top) ? (YGFloatIsUndefined(all) ? 0 : all) : top;
    vec4.x = YGFloatIsUndefined(right) ? (YGFloatIsUndefined(all) ? 0 : all) : right;
    vec4.y = YGFloatIsUndefined(bottom) ? (YGFloatIsUndefined(all) ? 0 : all) : bottom;
    vec4.z = YGFloatIsUndefined(left) ? (YGFloatIsUndefined(all) ? 0 : all) : left;

    return vec4;
  }

  bool GuiElement::isValidElement() {
    for (auto [attribute, isSet] : requiredAttributes) {
      if (!isSet) {
        return false;
      }
    }

    return true;
  }

  bool GuiElement::isValidTree() {
    if (!isValidElement()) {
      return false;
    }

    for (auto child : children) {
      if (!child->isValidTree()) {
        return false;
      }
    }

    return true;
  }

  void GuiElement::debugLayout() {
    fmt::println("Node: {} Position: ({}, {}) Size: ({}, {})", title, YGNodeLayoutGetLeft(node),
                 YGNodeLayoutGetTop(node), YGNodeLayoutGetWidth(node), YGNodeLayoutGetHeight(node));
  }
}  // namespace Zero