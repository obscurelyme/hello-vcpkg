#include "game/entities/player.h"

#include <raymath.h>

#include "Logging/core.hpp"
#include "ecs/components/transform.h"

void Zero::Player::init() { ConsoleLog("Player Created!"); }

void Zero::Player::ready() {
  transform = getComponent<Transform2D>();
  ConsoleLog("Player Ready!");
}

void Zero::Player::update(float deltaTime) {
  direction.x = static_cast<int>(IsKeyDown(KeyboardKey::KEY_D)) - static_cast<int>(IsKeyDown(KeyboardKey::KEY_A));
  direction.y = static_cast<int>(IsKeyDown(KeyboardKey::KEY_S)) - static_cast<int>(IsKeyDown(KeyboardKey::KEY_W));
  direction = Vector2Normalize(direction);
  direction = Vector2Scale(direction, speed * deltaTime);

  transform->position = Vector2Add(transform->position, direction);
}

void Zero::Player::physicsUpdate(float) {}

void Zero::Player::destroy() { ConsoleLog("Player Destroyed!"); }