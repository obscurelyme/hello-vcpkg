#ifndef ZERO_EDITOR_XMLPARSE_H_
#define ZERO_EDITOR_XMLPARSE_H_

#include <tinyxml2.h>

#include "Editor/guielement.h"
#include "Editor/guiroot.h"

namespace Zero {
  class XmlParse {
    public:
      explicit XmlParse();
      ~XmlParse();

      void unmarshal(GuiRoot* root);
      GuiElement* process(GuiRoot* root, tinyxml2::XMLElement* element, int depth = 0);

      tinyxml2::XMLDocument doc;
  };
}  // namespace Zero

#endif