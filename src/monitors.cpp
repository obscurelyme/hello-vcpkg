#include "monitors/monitors.h"

#include <raylib.h>

std::string Zero::MonitorsManager::currentMonitorName() {
  const char* cname = GetMonitorName(GetCurrentMonitor());
  return std::string{cname};
}

int Zero::MonitorsManager::currentRefreshRate() { return GetMonitorRefreshRate(GetCurrentMonitor()); }

int Zero::MonitorsManager::getMonitorCount() { return GetMonitorCount(); }

void Zero::MonitorsManager::setActiveMonitor(const int monitor) { SetWindowMonitor(monitor); }

void Zero::MonitorsManager::toggleVsync(const bool enabled) {
  if (enabled) {
    SetWindowState(FLAG_VSYNC_HINT);
  } else {
    ClearWindowState(FLAG_VSYNC_HINT);
  }
}

void Zero::MonitorsManager::toggleFullscreen() { ToggleBorderlessWindowed(); }