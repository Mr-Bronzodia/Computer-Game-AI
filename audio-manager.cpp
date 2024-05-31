#include "audio-manager.hpp"

namespace aipfg
{

AudioManager::AudioManager() :
    audio_{},
    coin_sound_{ "../resources/audio/coin.wav" },
    music_{ "../resources/audio/Magic-Clock-Shop.mp3" }
  {
    music_.Play();
  }

void AudioManager::hush()   { music_.SetVolume(music_volume_quiet); }
void AudioManager::dehush() { music_.SetVolume(music_volume_normal); }
void AudioManager::update() { music_.Update(); }

} // namespace aipfg
