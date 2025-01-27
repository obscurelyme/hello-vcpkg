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
      virtual void setWidth(float width, bool percent = false);
      virtual void setHeight(float height, bool percent = false);

      virtual float getWidth();
      virtual float getHeight();
      virtual float getTop();
      virtual float getLeft();

      virtual void addChild(GuiElement* element);
      virtual void removeChild(GuiElement* element);
      virtual void drawChildren();
      virtual void setFlexStyles(const Flex&);
      virtual void setStyles(const Styles&);
      virtual void setBorder(const Border&);
      virtual void setMargin(const Margin&);
      virtual void setPadding(const Padding&);

      YGNodeRef node{nullptr};
  };
}  // namespace Zero

#endif  // ZERO_EDITOR_GUI_ELEMENT_H_