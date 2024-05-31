#include "pc.hpp"
#include "sprite.hpp"
#include "game-manager.hpp"
#include <iostream>
#include <string>

#define collider_offset Vector2{35,60}

namespace aipfg
{

PC::PC(GameManager& gm, Sprite& sprite, const std::string& name, Collider* collider)
  : Sprite{ sprite }, name_{ name }, gm_{ gm }, player_collider{ collider }
{
  gm_.pc_ = this;
  hp_max = 100.f;
  hp = 90.0f;
  might = 5.0f;
  dmg = 2.0f;
  shield = 0.0f;
  playable_area = Rectangle{ 12, 10, 1000, 553 };
}

void PC::update()
{
  animation_on_ = false;
  
  //Hold D for player debug info
  if (IsKeyPressed(KEY_D)) {
      std::cout << "DEBUG: PC stats: " << hp << " " << hp_max << " " << might << " " << dmg << " " << shield << std::endl;
  }

  if (posn_.x + collider_offset.x <= playable_area.x) posn_.x += collider_offset.x / 2;
  if (posn_.x + collider_offset.x >= playable_area.x + playable_area.width) posn_.x -= collider_offset.x / 2;
  if (posn_.y + collider_offset.y <= playable_area.y) posn_.y += collider_offset.y / 2;
  if (posn_.y + collider_offset.y >= playable_area.y + playable_area.height) posn_.x -= collider_offset.y / 2;

  if (!gm_.text_box_)
  {   
    if (IsKeyDown(KEY_DOWN))
    {
        float next_position = posn_.y + speed_ * GetFrameTime();
        if (next_position + collider_offset.y < playable_area.y + playable_area.height) {
            posn_.y += speed_ * GetFrameTime();
            set_state("down");
        }
    }
    if (IsKeyDown(KEY_UP))
    {
        float next_position = posn_.y - speed_ * GetFrameTime();
        if (next_position + collider_offset.y > playable_area.y) {
            posn_.y -= speed_ * GetFrameTime();
            set_state("up");
        }
      
    }
    if (IsKeyDown(KEY_LEFT))
    {
        float next_position = posn_.x - speed_ * GetFrameTime();
        if (next_position + (collider_offset.x / 2) > playable_area.x) {
            posn_.x -= speed_ * GetFrameTime();
            set_state("left");
        }
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        float next_position = posn_.x + speed_ * GetFrameTime();
        if (next_position + collider_offset.x < playable_area.x + playable_area.width) {
            posn_.x += speed_ * GetFrameTime();
            set_state("right");
        }
    }

    player_collider->get_bounds()->set_bounding_centre(Vector2{ posn_.x + collider_offset.x, posn_.y + collider_offset.y });
  }

  Sprite::update();
}

void PC::draw() 
{
    Sprite::draw();
}

void PC::set_playable_area(Rectangle& area)
{
    playable_area = area;
}

} // namespace aipfg


