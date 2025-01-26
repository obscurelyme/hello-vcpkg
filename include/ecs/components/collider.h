#ifndef ZERO_COMPONENTS_COLLIDER_H_
#define ZERO_COMPONENTS_COLLIDER_H_

#include <raylib.h>

#include "component.h"

namespace Zero {
  class Collider2D : public Component {
    public:
      explicit Collider2D();
      virtual ~Collider2D() { ConsoleDebug("Destroying Collider2D component"); }

      Rectangle rect;
  };
}  // namespace Zero

#endif