#include "game-manager.hpp"
#include "audio-manager.hpp"
#include "openai-helper.hpp"
#include "text-box.hpp"
#include "raylib-cpp.hpp"
#include "pc.hpp"

namespace aipfg
{

GameManager::GameManager(raylib::Window& window)
  : am_{}, text_box_{}, window_{ window }, oai_help_{}, pc_{} {}

void GameManager::update()
{
  am_.update();
  if (text_box_)
  {
    if (false == (*text_box_).update()) // make text_box_ a member of GameManager
    {
      text_box_ = nullptr;
      am_.dehush();
    }
  }

  //if reapHeal is set to true within ai helper, then heal the player and reset.
  if (oai_help_.reapHeal) {
      std::cout << "DEBUG: Game Manager recived reapHeal \n" << std::endl;
      oai_help_.reapHeal = false;
      pc_->hp += 100;
      pc_->might -= 1;
  }

  if (oai_help_.upgrHP) {
      oai_help_.upgrHP = false;
      pc_->hp += 25;
  }

  //if (pc_->might == 0 && pc_->hp == 0);
  //std::cout << "DEBUG: Player died \n\n" << std::endl;
  //window_.Close();
}

void GameManager::draw()
{
  if (text_box_)
  {
    (*text_box_).draw();
  }

  //plyStats.clear();
  //plyStats.append("HP: ");
  //plyStats.append(std::to_string(pc_->hp));
  //plyStats.append(" Might: ");
  //plyStats.append(std::to_string(pc_->might));
  //raylib::DrawText(plyStats, 400, 500, 40, raylib::Color(BLACK));
}

} // namespace aipfg
