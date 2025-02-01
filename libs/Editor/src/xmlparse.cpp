#include "Editor/xmlparse.h"

#include <fmt/base.h>
#include <fmt/format.h>
#include <raylib.h>
#include <tinyxml2.h>

#include <filesystem>
#include <string>
#include <unordered_map>

#include "Editor/guielement.h"
#include "Editor/guipanel.h"
#include "Editor/guiroot.h"
#include "Editor/guitext.h"
#include "Editor/guiview.h"
#include "Editor/types.h"

namespace Zero {
  using MakeGuiElementFunc = GuiElement* (*)();

  GuiElement* makePanelElement() { return static_cast<GuiElement*>(new GuiPanel()); }
  GuiElement* makeViewElement() { return static_cast<GuiElement*>(new GuiView()); }
  GuiElement* makeTextElement() { return static_cast<GuiElement*>(new GuiText()); }

  const std::filesystem::path appDir = GetApplicationDirectory();
  const std::string resourcesPath = "resources";
  const std::string guiPath = "gui";
  const std::string editorFile = "editor.xml";
  const std::unordered_map<std::string, MakeGuiElementFunc> guiElementMap = {
      {"Panel", makePanelElement}, {"View", makeViewElement}, {"Text", makeTextElement}};
  const std::unordered_map<std::string_view, Attribute> attrMap = {{"id", Attribute::Id},
                                                                   {"title", Attribute::Title},

                                                                   {"width", Attribute::Width},
                                                                   {"height", Attribute::Height},
                                                                   {"maxWidth", Attribute::MaxWidth},
                                                                   {"maxHeight", Attribute::MaxHeight},
                                                                   {"minWidth", Attribute::MinWidth},
                                                                   {"minHeight", Attribute::MinHeight},

                                                                   {"border", Attribute::Border},
                                                                   {"borderTop", Attribute::BorderTop},
                                                                   {"borderRight", Attribute::BorderRight},
                                                                   {"borderBottom", Attribute::BorderBottom},
                                                                   {"borderLeft", Attribute::BorderLeft},

                                                                   {"margin", Attribute::Margin},
                                                                   {"marginTop", Attribute::MarginTop},
                                                                   {"marginRight", Attribute::MarginRight},
                                                                   {"marginBottom", Attribute::MarginBottom},
                                                                   {"marginLeft", Attribute::MarginLeft},

                                                                   {"padding", Attribute::Padding},
                                                                   {"paddingTop", Attribute::PaddingTop},
                                                                   {"paddingRight", Attribute::PaddingRight},
                                                                   {"paddingBottom", Attribute::PaddingBottom},
                                                                   {"paddingLeft", Attribute::PaddingLeft},

                                                                   {"flexDirection", Attribute::FlexDirection},
                                                                   {"alignItems", Attribute::FlexAlignItems},
                                                                   {"alignSelf", Attribute::FlexAlignSelf},
                                                                   {"alignContent", Attribute::FlexAlignContent},
                                                                   {"justifyContent", Attribute::FlexJustifyContent},
                                                                   {"flexBasis", Attribute::FlexBasis},
                                                                   {"flexGrow", Attribute::FlexGrow},
                                                                   {"flexShrink", Attribute::FlexShrink},
                                                                   {"flexWrap", Attribute::FlexWrap},
                                                                   {"gap", Attribute::Gap},
                                                                   {"gap-row", Attribute::GapRow},
                                                                   {"gap-column", Attribute::GapColumn}};
  const std::unordered_map<std::string_view, Elements> elementMap = {
      {"Panel", Elements::Panel},         {"View", Elements::View},     {"Text", Elements::Text},
      {"InputText", Elements::InputText}, {"Button", Elements::Button}, {"Menu", Elements::Menu},
      {"MenuItem", Elements::MenuItem},   {"List", Elements::List},     {"ListItem", Elements::ListItem}};

  const std::filesystem::path editorFilePath = appDir / resourcesPath / guiPath / editorFile;

  XmlParse::XmlParse() { readFile(); }

  XmlParse::~XmlParse() { doc.Clear(); }

  void XmlParse::readFile() {
    doc.Clear();
    auto err = doc.LoadFile(editorFilePath.string().c_str());
    if (err != tinyxml2::XML_SUCCESS) {
      fmt::println("XMLPARSE: Failed to load editor.xml file");
    }
  }

  void XmlParse::unmarshal(GuiRoot* guiRoot) {
    auto root = doc.RootElement();
    if (root) {
      guiRoot->addChild(process(guiRoot, root));
    }
  }

  GuiElement* XmlParse::process(GuiRoot* guiRoot, tinyxml2::XMLElement* element, int depth) {
    std::string name = element->Name();
    std::string text = "";
    if (element->GetText()) {
      text = element->GetText();
    }

    if (!guiElementMap.contains(name)) {
      fmt::println(fmt::runtime("XMLPARSE: Unknown GUI element: {:s}"), name);
      return nullptr;
    }

    auto makeElement = guiElementMap.at(name);
    GuiElement* guiElement = makeElement();
    // NOTE: make all potential attributes for this new element.
    Flex flexStyles;
    Styles styles;
    Border border;
    Margin margin;
    Padding padding;
    Gap gap;

    fmt::println(fmt::runtime("Start Element: {:s}: {:s}"), name, text);

    auto elemType =
        elementMap.contains((std::string_view)name) ? elementMap.at((std::string_view)name) : Elements::Unknown;
    switch (elemType) {
      case Elements::Text: {
        guiElement->innerText = text;
        break;
      }
      default:
        break;
    }

    const tinyxml2::XMLAttribute* attribute = element->FirstAttribute();
    while (attribute) {
      fmt::println(fmt::runtime("Attribute: {:s}: {:s} = {:s}"), name, attribute->Name(), attribute->Value());

      std::string_view attrName = attribute->Name();
      auto attrType = attrMap.contains(attrName) ? attrMap.at(attrName) : Attribute::Unknown;

      // NOTE: make this better later...
      switch (attrType) {
        case Attribute::Id: {
          guiElement->setId(std::string{attribute->Value()});
          break;
        }
        case Attribute::Title: {
          guiElement->setTitle(std::string{attribute->Value()});
          break;
        }
        case Attribute::Width: {
          std::string v = attribute->Value();
          if (v.ends_with("%")) {
            v.pop_back();
            styles.widthIsPercent = true;
          }
          styles.width = std::stof(v);
          break;
        }
        case Attribute::Height: {
          std::string v = attribute->Value();
          if (v.ends_with("%")) {
            v.pop_back();
            styles.heightIsPercent = true;
          }
          styles.height = std::stof(v);
          break;
        }
        case Attribute::MaxWidth: {
          std::string v = attribute->Value();
          if (v.ends_with("%")) {
            v.pop_back();
            styles.maxWidthIsPercent = true;
          }
          styles.maxWidth = std::stof(v);
          break;
        }
        case Attribute::MaxHeight: {
          std::string v = attribute->Value();
          if (v.ends_with("%")) {
            v.pop_back();
            styles.maxHeightIsPercent = true;
          }
          styles.maxHeight = std::stof(v);
          break;
        }
        case Attribute::MinWidth: {
          std::string v = attribute->Value();
          if (v.ends_with("%")) {
            v.pop_back();
            styles.minWidthIsPercent = true;
          }
          styles.minWidth = std::stof(v);
          break;
        }
        case Attribute::MinHeight: {
          std::string v = attribute->Value();
          if (v.ends_with("%")) {
            v.pop_back();
            styles.minHeightIsPercent = true;
          }
          styles.minHeight = std::stof(v);
          break;
        }
        case Attribute::Border: {
          border.all = attribute->FloatValue();
          break;
        }
        case Attribute::BorderTop: {
          border.top = attribute->FloatValue();
          break;
        }
        case Attribute::BorderRight: {
          border.right = attribute->FloatValue();
          break;
        }
        case Attribute::BorderBottom: {
          border.bottom = attribute->FloatValue();
          break;
        }
        case Attribute::BorderLeft: {
          border.left = attribute->FloatValue();
          break;
        }
        case Attribute::Margin: {
          margin.all = attribute->FloatValue();
          break;
        }
        case Attribute::MarginTop: {
          margin.top = attribute->FloatValue();
          break;
        }
        case Attribute::MarginRight: {
          margin.right = attribute->FloatValue();
          break;
        }
        case Attribute::MarginBottom: {
          margin.bottom = attribute->FloatValue();
          break;
        }
        case Attribute::MarginLeft: {
          margin.left = attribute->FloatValue();
          break;
        }
        case Attribute::Padding: {
          padding.all = attribute->FloatValue();
          break;
        }
        case Attribute::PaddingTop: {
          padding.top = attribute->FloatValue();
          break;
        }
        case Attribute::PaddingRight: {
          padding.right = attribute->FloatValue();
          break;
        }
        case Attribute::PaddingBottom: {
          padding.bottom = attribute->FloatValue();
          break;
        }
        case Attribute::PaddingLeft: {
          padding.left = attribute->FloatValue();
          break;
        }
        case Attribute::FlexDirection: {
          std::string_view v = attribute->Value();
          if (v == "row") {
            flexStyles.flexDirection = FlexDirection::YGFlexDirectionRow;
          } else if (v == "column") {
            flexStyles.flexDirection = FlexDirection::YGFlexDirectionColumn;
          } else if (v == "row-reverse") {
            flexStyles.flexDirection = FlexDirection::YGFlexDirectionRowReverse;
          } else if (v == "column-reverse") {
            flexStyles.flexDirection = FlexDirection::YGFlexDirectionColumnReverse;
          }
          break;
        }
        case Attribute::FlexAlignItems: {
          std::string_view v = attribute->Value();
          if (v == "center") {
            flexStyles.flexAlignItems = FlexAlign::YGAlignCenter;
          } else if (v == "flex-start") {
            flexStyles.flexAlignItems = FlexAlign::YGAlignFlexStart;
          } else if (v == "flex-end") {
            flexStyles.flexAlignItems = FlexAlign::YGAlignFlexEnd;
          } else if (v == "stretch") {
            flexStyles.flexAlignItems = FlexAlign::YGAlignStretch;
          } else if (v == "auto") {
            flexStyles.flexAlignItems = FlexAlign::YGAlignAuto;
          } else if (v == "baseline") {
            flexStyles.flexAlignItems = FlexAlign::YGAlignBaseline;
          } else if (v == "space-around") {
            flexStyles.flexAlignItems = FlexAlign::YGAlignSpaceAround;
          } else if (v == "space-between") {
            flexStyles.flexAlignItems = FlexAlign::YGAlignSpaceBetween;
          } else if (v == "space-evenly") {
            flexStyles.flexAlignItems = FlexAlign::YGAlignSpaceEvenly;
          }
          break;
        }
        case Attribute::FlexAlignSelf: {
          std::string_view v = attribute->Value();
          if (v == "center") {
            flexStyles.flexAlignSelf = FlexAlign::YGAlignCenter;
          } else if (v == "flex-start") {
            flexStyles.flexAlignSelf = FlexAlign::YGAlignFlexStart;
          } else if (v == "flex-end") {
            flexStyles.flexAlignSelf = FlexAlign::YGAlignFlexEnd;
          } else if (v == "stretch") {
            flexStyles.flexAlignSelf = FlexAlign::YGAlignStretch;
          } else if (v == "auto") {
            flexStyles.flexAlignSelf = FlexAlign::YGAlignAuto;
          } else if (v == "baseline") {
            flexStyles.flexAlignSelf = FlexAlign::YGAlignBaseline;
          } else if (v == "space-around") {
            flexStyles.flexAlignSelf = FlexAlign::YGAlignSpaceAround;
          } else if (v == "space-between") {
            flexStyles.flexAlignSelf = FlexAlign::YGAlignSpaceBetween;
          } else if (v == "space-evenly") {
            flexStyles.flexAlignSelf = FlexAlign::YGAlignSpaceEvenly;
          }
          break;
        }
        case Attribute::FlexAlignContent: {
          std::string_view v = attribute->Value();
          if (v == "center") {
            flexStyles.flexAlignContent = FlexAlign::YGAlignCenter;
          } else if (v == "flex-start") {
            flexStyles.flexAlignContent = FlexAlign::YGAlignFlexStart;
          } else if (v == "flex-end") {
            flexStyles.flexAlignContent = FlexAlign::YGAlignFlexEnd;
          } else if (v == "stretch") {
            flexStyles.flexAlignContent = FlexAlign::YGAlignStretch;
          } else if (v == "auto") {
            flexStyles.flexAlignContent = FlexAlign::YGAlignAuto;
          } else if (v == "baseline") {
            flexStyles.flexAlignContent = FlexAlign::YGAlignBaseline;
          } else if (v == "space-around") {
            flexStyles.flexAlignContent = FlexAlign::YGAlignSpaceAround;
          } else if (v == "space-between") {
            flexStyles.flexAlignContent = FlexAlign::YGAlignSpaceBetween;
          } else if (v == "space-evenly") {
            flexStyles.flexAlignContent = FlexAlign::YGAlignSpaceEvenly;
          }
          break;
        }
        case Attribute::FlexJustifyContent: {
          std::string_view v = attribute->Value();
          if (v == "center") {
            flexStyles.flexJustify = FlexJustify::YGJustifyCenter;
          } else if (v == "flex-start") {
            flexStyles.flexJustify = FlexJustify::YGJustifyFlexStart;
          } else if (v == "flex-end") {
            flexStyles.flexJustify = FlexJustify::YGJustifyFlexEnd;
          } else if (v == "space-around") {
            flexStyles.flexJustify = FlexJustify::YGJustifySpaceAround;
          } else if (v == "space-between") {
            flexStyles.flexJustify = FlexJustify::YGJustifySpaceBetween;
          } else if (v == "space-evenly") {
            flexStyles.flexJustify = FlexJustify::YGJustifySpaceEvenly;
          }
          break;
        }
        case Attribute::FlexBasis: {
          flexStyles.flexBasis = attribute->FloatValue();
          break;
        }
        case Attribute::FlexGrow: {
          flexStyles.flexGrow = attribute->FloatValue();
          break;
        }
        case Attribute::FlexShrink: {
          flexStyles.flexShrink = attribute->FloatValue();
          break;
        }
        case Attribute::FlexWrap: {
          std::string_view v = attribute->Value();
          if (v == "wrap") {
            flexStyles.flexWrap = FlexWrap::YGWrapWrap;
          } else if (v == "nowrap") {
            flexStyles.flexWrap = FlexWrap::YGWrapNoWrap;
          } else if (v == "wrap-reverse") {
            flexStyles.flexWrap = FlexWrap::YGWrapWrapReverse;
          }
          break;
        }
        case Attribute::Gap: {
          gap.all = attribute->FloatValue();
          break;
        }
        case Attribute::GapRow: {
          gap.row = attribute->FloatValue();
          break;
        }
        case Attribute::GapColumn: {
          gap.column = attribute->FloatValue();
          break;
        }
        default:
          break;
      }

      attribute = attribute->Next();
    }

    // NOTE: set all the styles for this element
    guiElement->setFlexStyles(flexStyles);
    guiElement->setStyles(styles);
    guiElement->setBorder(border);
    guiElement->setMargin(margin);
    guiElement->setPadding(padding);
    guiElement->setGap(gap);

    tinyxml2::XMLElement* child = element->FirstChildElement();
    while (child) {
      GuiElement* c = process(guiRoot, child, depth + 1);

      // NOTE: add child to current element, if one was returned
      if (c != nullptr) {
        guiElement->addChild(c);
      }

      child = child->NextSiblingElement();
    }

    fmt::println(fmt::runtime("End Element: {:s}"), name);

    return guiElement;
  }
}  // namespace Zero