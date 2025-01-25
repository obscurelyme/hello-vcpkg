#include "ecs/components/transform.h"

Zero::Transform2D::Transform2D() : Zero::Component() {
  type = ComponentType::Transform;
  ConsoleDebug("Initializing Transform2D component");
}