#include "game/entities/player.h"

#include <raymath.h>

#include <memory>

#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"


Zero::Player::Player() : Zero::Entity() {}

void Zero::Player::init() {
  this->spaceship = std::make_shared<Zero::Sprite>("spaceship.png");
  this->transform = std::make_shared<Zero::Transform2D>();

  // create more entities here...

  this->addComponent(this->spaceship);
  this->addComponent(this->transform);
}

void Zero::Player::ready() {}

void Zero::Player::update(float deltaTime) {
  direction.x = static_cast<int>(IsKeyDown(KeyboardKey::KEY_D)) - static_cast<int>(IsKeyDown(KeyboardKey::KEY_A));
  direction.y = static_cast<int>(IsKeyDown(KeyboardKey::KEY_S)) - static_cast<int>(IsKeyDown(KeyboardKey::KEY_W));
  direction = Vector2Normalize(direction);
  direction = Vector2Scale(direction, speed * deltaTime);

  transform->position = Vector2Add(transform->position, direction);

  // spaceship->position = Vector2Add(spaceship->position, direction);
}

void Zero::Player::physicsUpdate(float) {}

void Zero::Player::destroy() {}