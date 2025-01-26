#ifndef ZERO_GAME_PLAYER_H_
#define ZERO_GAME_PLAYER_H_

#include <raylib.h>

#include "ecs/components/transform.h"
#include "ecs/scriptableentity.h"

namespace Zero {
  class Player : public ScriptableEntity {
    public:
      void init() override;
      void ready() override;
      void update(float) override;
      void physicsUpdate(float) override;
      void destroy() override;

    private:
      Vector2 direction{.x = 0.0f, .y = 0.0f};
      float speed = 500.0f;

      Transform2D* transform{nullptr};
  };
}  // namespace Zero

#endif