#ifndef ZERO_ECS_ENTITY_H_
#define ZERO_ECS_ENTITY_H_

#include <fmt/format.h>

#include <entt/entt.hpp>
#include <stdexcept>
#include <string>

#include "Logging/core.hpp"
#include "scene/scene.h"

namespace Zero {
  using EntityId = entt::entity;

  class Entity {
    public:
      Entity();
      Entity(EntityId, Scene*);
      Entity(const Entity& other);
      virtual ~Entity() = default;
      operator bool() const { return id != entt::null; }
      Entity& operator=(const Entity& other);

      template <typename T, typename... Args>
      T& addComponent(Args&&... args) {
        if (hasComponent<T>()) {
          std::string err =
              fmt::format(fmt::runtime("Attempt to add duplicate component to Entity {:d} in Scene {:d}"), (int)id, 0);
          ConsoleErr(err);
          throw std::runtime_error{err};
        }
        return scene->registry.emplace<T>(id, std::forward<Args>(args)...);
      }

      template <typename T>
      bool hasComponent() {
        return scene->registry.all_of<T>(id);
      }

      template <typename T>
      T& getComponent() {
        if (!hasComponent<T>()) {
          std::string err = fmt::format(
              fmt::runtime("Attempt to get nonexistant component from Entity {:d} in Scene {:d}"), (int)id, 0);
          ConsoleErr(err);
          throw std::runtime_error{err};
        }
        return scene->registry.get<T>(id);
      }

      template <typename T>
      void removeComponent() {
        scene->registry.remove<T>(id);
      }

    private:
      std::string uuid;
      EntityId id{entt::null};
      Scene* scene{nullptr};
      inline static std::string resourceName{"ENTITY: {:s}"};

      void printTrace(const std::string& str) { ConsoleTrace(fmt::format(fmt::runtime(resourceName), str)); }
  };  // namespace Zero
}  // namespace Zero

#endif