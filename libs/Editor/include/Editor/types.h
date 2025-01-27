#ifndef ZERO_EDITOR_TYPES_H_
#define ZERO_EDITOR_TYPES_H_

#include <imgui.h>
#include <raylib.h>
#include <yoga/Yoga.h>

namespace Zero {
  inline Color Background = {31, 31, 31, 255};         // rgb(35, 35, 35)
  inline Color DarkPaleBlue = {41, 58, 80, 255};       // rgb(41, 58, 80)
  inline Color MediumPaleBlue = {129, 165, 212, 255};  // #81a5d4
  inline Color VibrantBlue = {51, 110, 182, 255};      // #336eb6
  inline Color PaleGray = {190, 204, 222, 255};        // #beccde
  inline Color OfficeBlue = {112, 144, 183, 255};      // #7090b7
  inline Color OffWhite = {239, 238, 217, 255};        // rgb(239, 238, 217)

  using FlexDirection = YGFlexDirection;
  using FlexAlign = YGAlign;
  using FlexJustify = YGJustify;

  class Flex {
    public:
      // default FlexDirection::YGFlexDirectionColumn
      FlexDirection flexDirection{FlexDirection::YGFlexDirectionColumn};
      FlexAlign flexAlign{FlexAlign::YGAlignAuto};
      FlexJustify flexJustify{FlexJustify::YGJustifyFlexStart};
  };

  ImVec4 convertColor(const ::Color& color);
}  // namespace Zero

#endif  // ZERO_EDITOR_TYPES_H_