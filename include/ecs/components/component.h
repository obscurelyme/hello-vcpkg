#ifndef ZERO_COMPONENTS_COMPONENT_H_
#define ZERO_COMPONENTS_COMPONENT_H_

#include <Logging/core.hpp>
#include <memory>
#include <string>

namespace Zero {
  template <typename T>
  using SharedComponent = std::shared_ptr<T>;

  enum class ComponentType { Transform = 1, Renderable, Physics };

  class Component {
    public:
      Component();
      virtual ~Component() { ConsoleDebug("Destroying component"); };
      ComponentType type;
      // UUID of this component
      std::string componentId;
      // UUID of the entity this component is currently attached to.
      std::string entityId;
      bool active;

    private:
      static std::string nextComponentIds;
  };
}  // namespace Zero

#endif