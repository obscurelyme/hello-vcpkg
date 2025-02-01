// Define flat data structures to hold element properties
struct ElementProperties {
    std::string name;
    std::string text;
    Flex flexStyles;
    Styles styles;
    Border border;
    Margin margin;
    Padding padding;
    Gap gap;
    std::vector<size_t> childIndices;  // Store indices instead of pointers
};

// Use contiguous memory for elements
struct GuiElementPool {
    std::vector<ElementProperties> properties;
    std::vector<GuiElement*> elements;
};

class XmlParse {
    GuiElementPool elementPool;

    // First pass: collect all element data
    void collectElements(tinyxml2::XMLElement* element) {
      ElementProperties props;
      // Fill properties
      elementPool.properties.push_back(props);
    }

    // Second pass: construct hierarchy
    void constructHierarchy() {
      // Create elements in batch
      for (const auto& props : elementPool.properties) {
        elementPool.elements.push_back(guiElementMap.at(props.name)());
      }

      // Set up parent-child relationships
      for (size_t i = 0; i < elementPool.properties.size(); i++) {
        for (auto childIdx : elementPool.properties[i].childIndices) {
          elementPool.elements[i]->addChild(elementPool.elements[childIdx]);
        }
      }
    }
};

template <typename T>
class ElementPool {
    std::vector<T> elements;
    std::vector<bool> active;

  public:
    size_t allocate() {
      // Reuse freed slots or create new
    }
    void free(size_t index) {
      // Mark slot as available
    }
};

struct AttributeProcessor {
    static void processAttributes(ElementProperties& props, tinyxml2::XMLElement* element) {
      // Process all attributes in one pass
      const auto* attribute = element->FirstAttribute();
      while (attribute) {
        processAttribute(props, attribute);
        attribute = attribute->Next();
      }
    }
};

// 5. Deferred Style Application

void applyStyles(GuiElement* element, const ElementProperties& props) {
  // Apply styles in batch after hierarchy is constructed
  element->setFlexStyles(props.flexStyles);
  element->setStyles(props.styles);
  element->setBorder(props.border);
  element->setMargin(props.margin);
  element->setPadding(props.padding);
  element->setGap(props.gap);
}

namespace Zero {

  // Flat data structures to hold element properties
  struct GuiElementData {
      std::string name;
      std::string id;
      Elements type{Elements::Unknown};

      // Style properties
      Flex flexStyles{};
      Styles styles{};
      Border border{};
      Margin margin{};
      Padding padding{};
      Gap gap{};

      // Hierarchy info
      size_t parentIndex{SIZE_MAX};
      std::vector<size_t> childIndices;
  };

  class XmlParser {
    private:
      std::vector<GuiElementData> elementData;
      std::vector<GuiElement*> elements;

      size_t processElement(tinyxml2::XMLElement* element, size_t parentIndex = SIZE_MAX) {
        GuiElementData data;
        data.name = element->Name();
        data.parentIndex = parentIndex;

        // Process attributes
        const tinyxml2::XMLAttribute* attr = element->FirstAttribute();
        while (attr) {
          parseAttribute(attr, data);
          attr = attr->Next();
        }

        // Store element data
        size_t currentIndex = elementData.size();
        elementData.push_back(data);

        // Process children recursively
        auto child = element->FirstChildElement();
        while (child) {
          size_t childIndex = processElement(child, currentIndex);
          elementData[currentIndex].childIndices.push_back(childIndex);
          child = child->NextSiblingElement();
        }

        return currentIndex;
      }

      void constructHierarchy() {
        // First create all elements
        elements.resize(elementData.size());
        for (size_t i = 0; i < elementData.size(); i++) {
          elements[i] = createGuiElement(elementData[i]);
        }

        // Then set up parent-child relationships
        for (size_t i = 0; i < elementData.size(); i++) {
          const auto& data = elementData[i];
          auto element = elements[i];

          // Apply styles
          applyStyles(element, data);

          // Set up hierarchy
          for (size_t childIdx : data.childIndices) {
            element->addChild(elements[childIdx]);
          }
        }
      }

    public:
      GuiElement* parse(const char* xmlPath) {
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(xmlPath) != tinyxml2::XML_SUCCESS) {
          return nullptr;
        }

        // Clear previous data
        elementData.clear();
        elements.clear();

        // Process XML into flat data structures
        auto root = doc.RootElement();
        if (root) {
          processElement(root);
        }

        // Construct hierarchy
        constructHierarchy();

        // Return root element
        return elements.empty() ? nullptr : elements[0];
      }
  };

}  // namespace Zero

XmlParser parser;
GuiRoot* root = new GuiRoot();
if (auto parsed = parser.parse("editor.xml")) {
  root->addChild(parsed);
}

enum class AttributeType {
  Id,
  Width,
  Height,
  FlexDirection,
  JustifyContent,
  AlignItems,
  Margin,
  Padding,
  Border,
  Gap,
  Unknown
};

class XmlParser {
  private:
    static AttributeType getAttributeType(const char* name);
    static void parseFlexAttribute(GuiElementData& data, const char* name, const char* value);
    static void parseSizeAttribute(GuiElementData& data, const char* name, const char* value);
    static void parseSpacingAttribute(GuiElementData& data, const char* name, const char* value);
    void parseAttribute(const tinyxml2::XMLAttribute* attr, GuiElementData& data);
    // ... other members
};

AttributeType XmlParser::getAttributeType(const char* name) {
  static const std::unordered_map<std::string, AttributeType> typeMap = {
      {"id", AttributeType::Id},
      {"width", AttributeType::Width},
      {"height", AttributeType::Height},
      {"flex-direction", AttributeType::FlexDirection},
      {"justify-content", AttributeType::JustifyContent},
      {"align-items", AttributeType::AlignItems},
      {"margin", AttributeType::Margin},
      {"padding", AttributeType::Padding},
      {"border", AttributeType::Border},
      {"gap", AttributeType::Gap}};

  auto it = typeMap.find(name);
  return it != typeMap.end() ? it->second : AttributeType::Unknown;
}

void XmlParser::parseAttribute(const tinyxml2::XMLAttribute* attr, GuiElementData& data) {
  const char* name = attr->Name();
  const char* value = attr->Value();

  switch (getAttributeType(name)) {
    case AttributeType::Id:
      data.id = value;
      break;

    case AttributeType::Width:
    case AttributeType::Height:
      parseSizeAttribute(data, name, value);
      break;

    case AttributeType::FlexDirection:
    case AttributeType::JustifyContent:
    case AttributeType::AlignItems:
      parseFlexAttribute(data, name, value);
      break;

    case AttributeType::Margin:
    case AttributeType::Padding:
    case AttributeType::Border:
    case AttributeType::Gap:
      parseSpacingAttribute(data, name, value);
      break;

    default:
      fmt::println("Unknown attribute: {}", name);
      break;
  }
}

void XmlParser::parseFlexAttribute(GuiElementData& data, const char* name, const char* value) {
  if (strcmp(name, "flex-direction") == 0) {
    if (strcmp(value, "row") == 0)
      data.flexStyles.direction = FlexDirection::Row;
    else if (strcmp(value, "column") == 0)
      data.flexStyles.direction = FlexDirection::Column;
  }
  // Add other flex attribute parsing...
}

void XmlParser::parseSizeAttribute(GuiElementData& data, const char* name, const char* value) {
  float size = std::stof(value);
  bool isPercent = strchr(value, '%') != nullptr;

  if (strcmp(name, "width") == 0) {
    data.styles.width = size;
    data.styles.widthPercent = isPercent;
  } else if (strcmp(name, "height") == 0) {
    data.styles.height = size;
    data.styles.heightPercent = isPercent;
  }
}

void XmlParser::parseSpacingAttribute(GuiElementData& data, const char* name, const char* value) {
  std::vector<float> values;
  std::stringstream ss(value);
  std::string token;

  while (std::getline(ss, token, ' ')) {
    values.push_back(std::stof(token));
  }

  Vector4 spacing;
  switch (values.size()) {
    case 1:  // all sides
      spacing = {values[0], values[0], values[0], values[0]};
      break;
    case 2:  // vertical, horizontal
      spacing = {values[0], values[1], values[0], values[1]};
      break;
    case 4:  // top, right, bottom, left
      spacing = {values[0], values[1], values[2], values[3]};
      break;
  }

  if (strcmp(name, "margin") == 0)
    data.margin = spacing;
  else if (strcmp(name, "padding") == 0)
    data.padding = spacing;
  else if (strcmp(name, "border") == 0)
    data.border = spacing;
  else if (strcmp(name, "gap") == 0)
    data.gap = {values[0], values.size() > 1 ? values[1] : values[0]};
}