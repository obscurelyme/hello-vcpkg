#ifndef ZERO_COMPONENTS_TRANSFORM_H_
#define ZERO_COMPONENTS_TRANSFORM_H_

#include <raylib.h>

#include "ecs/components/component.h"

namespace Zero {
  class Transform2D : public Component {
    public:
      explicit Transform2D();
      virtual ~Transform2D() { ConsoleDebug("Destroying Transform2D component"); }
      Vector2 position{.x = 0.0f, .y = 0.0f};
      float rotation{0.0f};
      float scale{1.0f};
  };
}  // namespace Zero

#endif