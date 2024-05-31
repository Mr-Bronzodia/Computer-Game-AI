#ifndef _GAME_MANAGER_HPP_
#define _GAME_MANAGER_HPP_

#include "audio-manager.hpp"
#include "openai-helper.hpp"
#include "raylib-cpp.hpp"

namespace aipfg
{

class TextBox;
class PC;

class GameManager
{
public:
  GameManager(raylib::Window&);

  void update();
  void draw();

  AudioManager am_;
  TextBox* text_box_;
  raylib::Window& window_;
  openai_helper oai_help_;
  PC* pc_; // the player character
  std::string plyStats = "HP: ";
};

} // namespace aipfg

#endif // _GAME_MANAGER_HPP_
