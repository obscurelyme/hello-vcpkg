#ifndef ZERO_MONITORS_H_
#define ZERO_MONITORS_H_

#include <raylib.h>

#include <string>

namespace Zero {
  class MonitorsManager {
    public:
      MonitorsManager() = delete;
      MonitorsManager(const MonitorsManager&) = delete;
      MonitorsManager& operator=(const MonitorsManager&) = delete;
      ~MonitorsManager() = delete;
      // Returns the number of monitors available for use
      static int getMonitorCount();
      // Returns the refresh rate of the current active monitor
      static int currentRefreshRate();
      // Returns the name of the current monitor
      static std::string currentMonitorName();
      // Sets the monitor for the window
      static void setActiveMonitor(const int monitor);
      // Toggle Vsync for the active monitor
      static void toggleVsync(const bool enabled);
      static void toggleFullscreen();
      // Return the size of the current monitor
      static Vector2 monitorSize();
  };
}  // namespace Zero

#endif