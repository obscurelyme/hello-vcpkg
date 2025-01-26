#ifndef ZERO_COMPONENTS_AUDIO_H_
#define ZERO_COMPONENTS_AUDIO_H_

#include "component.h"

namespace Zero {
  class Audio : public Component {
    public:
      explicit Audio();
      virtual ~Audio() { ConsoleDebug("Destroying Audio component"); }
      // Play audio sound
      void play() {}
      // Stop the audio sound
      void stop() {}
  };
}  // namespace Zero

#endif