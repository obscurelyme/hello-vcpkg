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
      std::optional<FlexDirection> flexDirection{std::nullopt};
      std::optional<FlexAlign> flexAlign{std::nullopt};
      std::optional<FlexJustify> flexJustify{std::nullopt};
      std::optional<float> flexBasis{std::nullopt};
      std::optional<float> flex{std::nullopt};
      std::optional<float> flexGrow{std::nullopt};
      std::optional<float> flexShrink{std::nullopt};
      std::optional<FlexWrap> flexWrap{std::nullopt};
      std::optional<bool> useFlexBasisPercent{std::nullopt};
      std::optional<bool> flexBasisAuto{std::nullopt};
      std::optional<float> gap{std::nullopt};
      std::optional<float> gapRow{std::nullopt};
      std::optional<float> gapColumn{std::nullopt};
  };

  class Border {
    public:
      std::optional<float> all{std::nullopt};
      std::optional<float> top{std::nullopt};
      std::optional<float> right{std::nullopt};
      std::optional<float> bottom{std::nullopt};
      std::optional<float> left{std::nullopt};
  };

  class Margin {
    public:
      std::optional<float> all{std::nullopt};
      std::optional<float> top{std::nullopt};
      std::optional<float> right{std::nullopt};
      std::optional<float> bottom{std::nullopt};
      std::optional<float> left{std::nullopt};
  };

  class Padding {
    public:
      std::optional<float> all{std::nullopt};
      std::optional<float> top{std::nullopt};
      std::optional<float> right{std::nullopt};
      std::optional<float> bottom{std::nullopt};
      std::optional<float> left{std::nullopt};
  };

  // Style input options for GuiElements
  class Styles {
    public:
      std::optional<float> width{std::nullopt};
      std::optional<float> height{std::nullopt};
      std::optional<float> maxWidth{std::nullopt};
      std::optional<float> maxHeight{std::nullopt};
      std::optional<float> minWidth{std::nullopt};
      std::optional<float> minHeight{std::nullopt};

      std::optional<Border> border{std::nullopt};
      std::optional<Margin> margin{std::nullopt};
      std::optional<Padding> padding{std::nullopt};
  };

  ImVec4 convertColor(const ::Color& color);
}  // namespace Zero

#endif  // ZERO_EDITOR_TYPES_H_