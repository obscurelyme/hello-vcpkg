#ifndef ZERO_EDITOR_TYPES_H_
#define ZERO_EDITOR_TYPES_H_

#include <imgui.h>
#include <raylib.h>
#include <yoga/Yoga.h>

#include <optional>

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
  using FlexWrap = YGWrap;
  using BoxSizing = YGBoxSizing;
  using Gutter = YGGutter;
  using Edge = YGEdge;

  // Flex input options for GuiElements
  class Flex {
    public:
      std::optional<FlexDirection> flexDirection;
      std::optional<FlexAlign> flexAlign;
      std::optional<FlexJustify> flexJustify;
      std::optional<float> flexBasis;
      std::optional<float> flex;
      std::optional<float> flexGrow;
      std::optional<float> flexShrink;
      std::optional<FlexWrap> flexWrap;
      std::optional<bool> useFlexBasisPercent;
      std::optional<bool> flexBasisAuto;
      std::optional<float> gap;
      std::optional<float> gapRow;
      std::optional<float> gapColumn;
  };

  class Border {
    public:
      std::optional<float> all;
      std::optional<float> top;
      std::optional<float> right;
      std::optional<float> bottom;
      std::optional<float> left;
  };

  class Margin {
    public:
      std::optional<float> all;
      std::optional<float> top;
      std::optional<float> right;
      std::optional<float> bottom;
      std::optional<float> left;
  };

  class Padding {
    public:
      std::optional<float> all;
      std::optional<float> top;
      std::optional<float> right;
      std::optional<float> bottom;
      std::optional<float> left;
  };

  // Style input options for GuiElements
  class Styles {
    public:
      std::optional<float> width;
      std::optional<float> height;
      std::optional<float> maxWidth;
      std::optional<float> maxHeight;
      std::optional<float> minWidth;
      std::optional<float> minHeight;

      std::optional<Border> border;
      std::optional<Margin> margin;
      std::optional<Padding> padding;
  };

  ImVec4 convertColor(const ::Color& color);
}  // namespace Zero

#endif  // ZERO_EDITOR_TYPES_H_