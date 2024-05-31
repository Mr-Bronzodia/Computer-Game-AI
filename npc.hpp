#ifndef _NPC_HPP_
#define _NPC_HPP_

#include "sprite.hpp"
#include "game-manager.hpp"
#include "text-box.hpp"
#include "raylib-cpp.hpp"
#include <future>     // std::async
#include <functional> // std::ref
#include <iostream>

namespace aipfg
{

class NPC : public Sprite
{
public:
  NPC(GameManager&, Sprite&, const std::string&, const TextBoxParams&);

  void update();
  void draw();
  void text_box_wait();

private:

  bool colliding_{ false };

  GameManager& gm_;

  const std::string name_;
  TextBox text_box_;
};

} // namespace aipfg

#endif // _NPC_HPP_
