#include "textures/textures.h"

#include <raylib.h>

#include "Logging/core.hpp"

const std::string assetsDir = "assets";
const std::filesystem::path Zero::Texture2D::assetDir = std::filesystem::current_path() / assetsDir;

Zero::Texture2D::Texture2D(const std::string& fileName) noexcept {
  this->filePath = (this->assetDir / fileName).string();
  this->texture = LoadTexture(this->filePath.c_str());
  this->position = Vector2{.x = 0.0f, .y = 0.0f};
  this->tint = WHITE;
}

Zero::Texture2D::~Texture2D() noexcept {
  if (IsTextureValid(this->texture)) {
    UnloadTexture(this->texture);
    return;
  }
  ConsoleErr("Unable to unload texture because it was not loaded into the GPU");
}

unsigned int Zero::Texture2D::id() noexcept { return this->texture.id; }

::PixelFormat Zero::Texture2D::format() noexcept { return static_cast<::PixelFormat>(this->texture.format); }

::Texture2D Zero::Texture2D::get() noexcept { return this->texture; }

void Zero::Texture2D::draw() noexcept { DrawTextureV(this->texture, this->position, this->tint); }