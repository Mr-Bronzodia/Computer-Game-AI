#ifndef _AUDIO_MANAGER_HPP_
#define _AUDIO_MANAGER_HPP_

#include "raylib-cpp.hpp"

namespace aipfg
{

class AudioManager
{
public:
  AudioManager();

  void hush();
  void dehush();
  void update();

  raylib::AudioDevice audio_; // necessary: initialises the audio
  raylib::Music music_;
  raylib::Sound coin_sound_;
  const float music_volume_normal = 1.0f, music_volume_quiet = 0.4f;
};

} // namespace aipfg

#endif // _AUDIO_MANAGER_HPP_
