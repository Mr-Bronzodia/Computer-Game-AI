#include "npc.hpp"
#include "pc.hpp"
#include "sprite.hpp"
#include "game-manager.hpp"
#include "text-box.hpp"
#include "raylib-cpp.hpp"
#include <future>     // std::async
#include <functional> // std::ref
#include <iostream>

namespace aipfg
{

NPC::NPC(GameManager& gm, Sprite& sprite, const std::string& name,
         const TextBoxParams& tbp)
    : Sprite{ sprite }, gm_{ gm }, name_{ name },
      text_box_{ gm, tbp.nature_, tbp.gambit_, name + ": " }
  {
  }

void NPC::update()
{
  if (Vector2Distance(gm_.pc_->posn_, Sprite::posn_) < 30.0f)
  {
    if (!colliding_)
    {
      colliding_ = true;

      gm_.text_box_ = &text_box_;
      SetExitKey(0);
      gm_.am_.coin_sound_.Play();
      gm_.am_.hush();
    }
  }
  else
  {
    colliding_ = false;
  }
}

void NPC::draw() { Sprite::draw(); text_box_.draw(); }
void NPC::text_box_wait()
{
  if (text_box_.response_future_.valid())
  {
    text_box_.response_future_.wait();
  }
}

} // namespace aipfg
