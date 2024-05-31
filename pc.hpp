#ifndef _PC_HPP_
#define _PC_HPP_

#include "sprite.hpp"
#include "game-manager.hpp"
#include "Bounds.h"
#include "Collider.h"
#include <string>

namespace aipfg
{

class PC : public Sprite
{
public:
  PC(GameManager&, Sprite&, const std::string&, Collider*);

  void reaper_heal();
  void update();
  void draw();

  void set_playable_area(Rectangle& area);

  std::string name_;
  float speed_{ 120.0f };
  GameManager& gm_;
  Rectangle playable_area;
  Collider* player_collider;
  //add player attributes as written in document

  float hp;
  float hp_max;
  float might;
  float dmg;
  float shield;
};

} // namespace aipfg

#endif // _PC_HPP_
