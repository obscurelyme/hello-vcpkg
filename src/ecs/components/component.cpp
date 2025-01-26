#include "ecs/components/component.h"

#include "uuid/uuid.h"

Zero::Component::Component() {
  componentId = randomUUID();
  active = true;
  ConsoleDebug("Initializing component");
}