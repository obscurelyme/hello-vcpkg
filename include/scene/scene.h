#ifndef ZERO_SCENE_H_
#define ZERO_SCENE_H_

#include <entt/entt.hpp>

#include "utils/memory.h"

namespace Zero {
  class Entity;

  class Scene {
    public:
      Scene();
      ~Scene();

      void processInits();
      void processReadies();
      void processUpdates(float);
      void processPhysicsUpdates(float);
      void processDestroys();
      void render();

      Entity createEntity();
      void addToScene(Entity*);

    private:
      // Registry of entities for this scene.
      entt::registry registry;

      friend class Entity;
  };

  Ref<Scene> CreateNewScene();
  void SetActiveScene(const Ref<Scene>& scene);
  Ref<Scene> GetActiveScene();
  void ProcessInits();
  void ProcessReadies();
  void ProcessUpdates(float);
  float ProcessPhysicsUpdates(float, float);
  void ProcessDestroys();
  void Render();
}  // namespace Zero

#endif