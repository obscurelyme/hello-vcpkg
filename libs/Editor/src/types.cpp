#include "Editor/types.h"

#include <rlImGuiColors.h>


namespace Zero {
  ImVec4 convertColor(const ::Color& color) { return rlImGuiColors::Convert(color); }
}  // namespace Zero