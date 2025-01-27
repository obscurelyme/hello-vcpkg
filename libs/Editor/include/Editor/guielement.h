#ifndef ZERO_EDITOR_GUI_ELEMENT_H_
#define ZERO_EDITOR_GUI_ELEMENT_H_

#include <yoga/Yoga.h>

#include "Editor/types.h"

namespace Zero {
  // Interface for all Editor GUI elements
  class GuiElement {
    public:
      explicit GuiElement();
      virtual ~GuiElement();
      virtual void draw();
      virtual void setWidth(float width);
      virtual void setHeight(float height);

      virtual float getWidth();
      virtual float getHeight();
      virtual float getTop();
      virtual float getLeft();

      virtual void addChild(GuiElement* element);
      virtual void removeChild(GuiElement* element);
      virtual void drawChildren();
      virtual void setFlexStyles(const Flex&);

      YGNodeRef node{nullptr};
  };
}  // namespace Zero

#endif  // ZERO_EDITOR_GUI_ELEMENT_H_