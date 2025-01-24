#include "textures/textures.h"

#include <raylib.h>

#include "Logging/core.hpp"


std::filesystem::path Zero::Texture2D::assetDir = std::filesystem::current_path() / "assets";

Zero::Texture2D::Texture2D(const std::string& fileName) {
  this->filePath = (this->assetDir / fileName).string();
  this->texture = LoadTexture(this->filePath.c_str());
}

Zero::Texture2D::~Texture2D() {
  if (IsTextureValid(this->texture)) {
    UnloadTexture(this->texture);
    return;
  }
  ConsoleErr("Unable to unload texture because it was not loaded into the GPU");
}

unsigned int Zero::Texture2D::id() { return this->texture.id; }

::PixelFormat Zero::Texture2D::format() { return static_cast<::PixelFormat>(this->texture.format); }

::Texture2D Zero::Texture2D::get() { return this->texture; }