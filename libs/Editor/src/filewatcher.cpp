#include "Editor/filewatcher.h"

#include <filesystem>
#include <thread>

namespace Zero {
  FileWatcher::FileWatcher() {}

  FileWatcher::~FileWatcher() {
    if (watcherThread != nullptr && watcherThread->joinable()) {
      endWatching();
    }
    delete watcherThread;
  }

  void FileWatcher::startWatching(const std::filesystem::path& path, std::function<void()> onFileChanged) {
    if (watcherThread != nullptr) {
      return;
    }

    watchPath = path;
    lastWriteTime = std::filesystem::last_write_time(watchPath);
    watching = true;
    // NOTE: create the new thread to watch the file
    watcherThread = new std::thread([this, onFileChanged]() -> void {
      while (watching) {
        auto currentTime = std::filesystem::last_write_time(watchPath);
        if (currentTime != lastWriteTime) {
          lastWriteTime = currentTime;
          onFileChanged();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
      }
    });
  }

  void FileWatcher::endWatching() {
    watching = false;
    watcherThread->join();
  }
}  // namespace Zero