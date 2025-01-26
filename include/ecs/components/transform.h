#ifndef ZERO_COMPONENTS_TRANSFORM_H_
#define ZERO_COMPONENTS_TRANSFORM_H_

#include <raylib.h>

namespace Zero {
  class Transform2D {
    public:
      ~Transform2D() = default;
      Vector2 position{.x = 0.0f, .y = 0.0f};
      float rotation{0.0f};
      float scale{1.0f};
  };
}  // namespace Zero

#endif