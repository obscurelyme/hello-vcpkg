#include "ecs/components/renderable.h"

Zero::Renderable::Renderable() : Component() {
  type = ComponentType::Renderable;
  ConsoleDebug("Initializing renderable component");
}