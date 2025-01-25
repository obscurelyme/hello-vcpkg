#ifndef ZERO_COMPONENTS_RENDERABLE_H_
#define ZERO_COMPONENTS_RENDERABLE_H_

#include <Logging/core.hpp>

#include "component.h"

namespace Zero {
  class Renderable : public Component {
    public:
      explicit Renderable();
      virtual ~Renderable() { ConsoleDebug("Destroying renderable component"); }
      virtual void render() = 0;
  };

}  // namespace Zero

#endif