#ifndef ZERO_UTILS_MEMORY_H_
#define ZERO_UTILS_MEMORY_H_

#include <memory>
#include <utility>

namespace Zero {
  template <typename T>
  using Ref = std::shared_ptr<T>;

  template <typename T, typename... Args>
  Ref<T> MakeRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
}  // namespace Zero

#endif