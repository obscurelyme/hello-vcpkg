#ifndef ZERO_EDITOR_FILEWATCHER_H_
#define ZERO_EDITOR_FILEWATCHER_H_

#include <filesystem>
#include <functional>
#include <thread>

namespace Zero {
  class FileWatcher {
    public:
      FileWatcher();
      ~FileWatcher();
      void startWatching(const std::filesystem::path&, std::function<void()>);
      void endWatching();

    private:
      std::filesystem::path watchPath;
      std::thread* watcherThread{nullptr};
      std::atomic<bool> watching{false};
      std::filesystem::file_time_type lastWriteTime;
  };
}  // namespace Zero

#endif