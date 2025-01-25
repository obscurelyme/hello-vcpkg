#ifndef ZERO_COMPONENTS_COMPONENT_H_
#define ZERO_COMPONENTS_COMPONENT_H_

#include <Logging/core.hpp>
#include <memory>
#include <string>

namespace Zero {
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

  using SharedComponent = std::shared_ptr<Component>;
  template <typename T>
  using Shared = std::shared_ptr<T>;
}  // namespace Zero

#endif