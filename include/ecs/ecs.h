#ifndef ZERO_ECS_H_
#define ZERO_ECS_H_

#include <fmt/format.h>

#include <bitset>
#include <memory>
#include <unordered_map>

#include "Logging/core.hpp"
#include "uuid/uuid.h"

namespace Zero {
  using EntityId = std::string;
  using ComponentId = std::string;
  using ComponentBitset = std::bitset<32>;

  enum class ComponentType { Transform = 1, Renderable, Physics };

  class Component {
    public:
      Component() {
        id = randomUUID();
        active = true;
        ConsoleDebug("Initializing component");
      }
      virtual ~Component() { ConsoleDebug("Destroying component"); };
      ComponentType type;
      // uuid string
      ComponentId id;
      bool active;

    private:
      static ComponentId nextComponentIds;
  };

  class Renderable : public Component {
    public:
      explicit Renderable() : Component() {
        type = ComponentType::Renderable;
        ConsoleDebug("Initializing renderable component");
      }
      virtual ~Renderable() { ConsoleDebug("Destroying renderable component"); }
      virtual void render() = 0;
  };

  class Entity;
  inline std::unordered_map<EntityId, Entity*> entities;
  inline std::unordered_map<EntityId, Entity*> entitiesToInit;
  inline std::unordered_map<EntityId, Entity*> entitiesToMakeReady;
  inline std::unordered_map<EntityId, Entity*> entitiesToDestroy;

  class EntityManager {
    public:
      static EntityManager* Create() {
        if (instance == nullptr) {
          instance = new EntityManager();
          ConsoleLog("EntityManager successfully created");
        } else {
          ConsoleWarn("Attempt to recreate existing EntityManager failed");
        }

        return instance;
      }
      ~EntityManager() {
        entityComponentMask.clear();
        renderables.clear();
        ConsoleLog("EntityManager successfully destroyed");
      }
      static void AddComponent(EntityId entityId, std::shared_ptr<Component> component) {
        switch (component->type) {
          case Zero::ComponentType::Renderable: {
            auto convertedPtr = std::dynamic_pointer_cast<Renderable>(component);
            instance->renderables[entityId + component->id] = convertedPtr;
            instance->entityComponentMask[entityId + component->id].set(static_cast<int>(ComponentType::Renderable));
            break;
          }
          default: {
            ConsoleErr("Unknown component type added to entity manager, ignoring");
          }
        }
      }
      static void RemoveComponent(EntityId entityId, const std::shared_ptr<Component> component) {
        switch (component->type) {
          case Zero::ComponentType::Renderable: {
            auto convertedPtr = std::dynamic_pointer_cast<Renderable>(component);
            instance->renderables.erase(entityId + component->id);
            break;
          }
          default: {
            ConsoleErr("Unknown component type added to entity manager, ignoring");
          }
        }
      }
      static void Render() {
        for (auto it = instance->renderables.begin(); it != instance->renderables.end(); ++it) {
          it->second->render();
        }
      }
      static EntityManager* Get() { return instance; }
      static void Destroy() {
        Zero::entities.clear();
        Zero::entitiesToInit.clear();
        Zero::entitiesToMakeReady.clear();
        Zero::entitiesToDestroy.clear();
        delete instance;
      }

    private:
      static EntityManager* instance;
      EntityId nextEntityId;

      std::unordered_map<EntityId, ComponentBitset> entityComponentMask;
      std::unordered_map<EntityId, std::shared_ptr<Renderable>> renderables;
  };

  class Entity {
    public:
      explicit Entity() {
        this->id = randomUUID();
        entities[this->id] = this;
        entitiesToInit[this->id] = this;
        entitiesToMakeReady[this->id] = this;
      }
      virtual ~Entity() {
        // NOTE: remove this entity from all helper maps so that the lifetime methods aren't mistakenly invoked.
        entities.erase(this->id);
        entitiesToInit.erase(this->id);
        entitiesToMakeReady.erase(this->id);
        entitiesToDestroy.erase(this->id);
      };
      virtual void init() = 0;
      virtual void ready() = 0;
      virtual void update(float deltaTime) = 0;
      virtual void physicsUpdate() = 0;
      virtual void destroy() = 0;

      void addComponent(const std::shared_ptr<Component>& component) {
        EntityManager::AddComponent(this->id, component);
      }

      void removeComponent(const std::shared_ptr<Component>& component) {
        EntityManager::RemoveComponent(this->id, component);
      }

      // uuid string
      EntityId id;
  };  // namespace Zero
}  // namespace Zero

#endif