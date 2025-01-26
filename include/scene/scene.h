#ifndef ZERO_SCENE_H_
#define ZERO_SCENE_H_

#include <entt/entt.hpp>

#include "utils/memory.h"

namespace Zero {
  class Scene {
    public:
      Scene();
      ~Scene();

      void processInits();
      void processReadies();
      void processUpdates(float);
      void processPhysicsUpdates(float);
      void processDestroys();

      entt::entity createEntity();
      // Registry of entities for this scene.
      entt::registry entityRegistry;

      // private:
      // Registry of entities for this scene.
      // entt::registry entityRegistry;
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