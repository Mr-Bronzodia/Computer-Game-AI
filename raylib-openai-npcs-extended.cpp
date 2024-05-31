#pragma once

#include "sprite.hpp"
#include "pc.hpp"
#include "npc.hpp"
#include "game-manager.hpp"
#include "openai-helper.hpp"
#include "raylib-tileson.h"
#include "raylib-cpp.hpp"
#include "Level.h"
#include "Collider.h"
#include "pick-up.h"
#include "health-pickup.h"
#include "damage-pickup.h"
#include "speed-pickup.h"
#include "shield-pickup.h"
#include "player-ui.h"
#include "Enemy.h"
#include <string>     // std::string
#include <vector>     // std::vector
#include <numeric>    // std::iota
#include <iostream>   // std::cout
#include <future>     // std::async
#include <functional> // std::ref
#include <map>        // std::map
#include <algorithm>  // std::sort

// This version makes the call to OpenAI asynchronous; and add a resizable
// window. Also, Sprite class now removes set_* member functions, and a new NPC
// and PC class is added. Also added exception handler to OpenAI code.
// Sprite now has an update member function: more logical to update the
// animation here

aipfg::NPC make_reaper(aipfg::GameManager&, raylib::Texture&);
aipfg::NPC make_prisoner(aipfg::GameManager&, raylib::Texture&);
aipfg::NPC make_green_knight(aipfg::GameManager&, raylib::Texture&);
aipfg::Enemy make_enemy(raylib::Texture&, Vector2 pos);

int main(int argc, char *argv[])
{
  using namespace aipfg;

  raylib::Window window(1024, 576, "Colosseum of Might prototype ~ Team 3");
  window.SetState(FLAG_WINDOW_RESIZABLE);

  raylib::RenderTexture rt{ GetScreenWidth(), GetScreenHeight() };

  SetTargetFPS(60);            // Set our game to run at 60 frames-per-second

  GameManager gm{ window };


  raylib::Texture tex1{ "../resources/time_fantasy/knights_3x.png" };
  raylib::Texture player_tex{ "../resources/Knight/Run/Run-Sheet.png" };
  raylib::Texture prisoner_tex{ "../resources/tilemaps/Heroes/Rogue/Death/Death-Sheet.png" };
  raylib::Texture tex2{ "../resources/time_fantasy/reaper_blade_3.png" };
  raylib::Texture pickup_tex{ "../resources/health.png" };
  raylib::Texture dmg_tex{ "../resources/sword.png" };
  raylib::Texture speed_tex{ "../resources/hermes.png" };
  raylib::Texture shield_tex{ "../resources/shield.png" };

  int ncols = 6, nrows = 1;
  std::map<std::string, std::vector<int>> all_frame_ids;

  all_frame_ids["down"] = { 0,  1,  2,  3, 4, 5 };
  all_frame_ids["left"]  = { 0,  1,  2,  3, 4, 5 };
  all_frame_ids["right"] = { 0,  1,  2,  3, 4, 5 };
  all_frame_ids["up"]    = { 0,  1,  2,  3, 4, 5 };

  Sprite sprt { player_tex, ncols, nrows, { 115.5, 490 }, all_frame_ids, 6 };


  Collider pc_collider{ Bounds{Vector2{0, 0}, Vector2{8 , 8 }}, true };
  PC pc{ gm, sprt, "Human", &pc_collider};

  gm.pc_ = &pc;


  Enemy test = make_enemy(tex1, {200, 120});
  Enemy test2 = make_enemy(tex1, {120, 250});
  Enemy test3 = make_enemy(tex1, {60, 50 });


  std::vector<Enemy*> enemies{ &test, &test2, &test3 };


  //Collider{ Bounds{Vector2{623.5, 144.5}, Vector2{47.5, 46.5}}, false };

  std::vector<Collider*> colliders1_1{
    &Collider{Bounds{Vector2{71, 406}, Vector2{56, 38}}, true},
    &Collider{Bounds{Vector2{70.5, 166}, Vector2{56.5, 38}}, true},
    &Collider{Bounds{Vector2{242, 165}, Vector2{49, 37}}, true},
    &Collider{Bounds{Vector2{328, 166}, Vector2{38, 38}}, true},
    &Collider{Bounds{Vector2{328, 166}, Vector2{38, 38}}, true},
    &Collider{Bounds{Vector2{421.5, 166.5}, Vector2{57.5, 38.5}}, true},
    &Collider{Bounds{Vector2{503, 176.5}, Vector2{24, 25.5}}, true},
    &Collider{Bounds{Vector2{616.5, 167.5}, Vector2{86.5, 37.5}}, true},
    &Collider{Bounds{Vector2{679, 71}, Vector2{22, 57}}, true},
    &Collider{Bounds{Vector2{312, 492.5}, Vector2{21, 65.5}}, true},
    &Collider{Bounds{Vector2{311.5, 390.5}, Vector2{22.5, 22.5}}, true},
    &Collider{Bounds{Vector2{406.5, 405.5}, Vector2{72.5, 37.5}}, true},
    &Collider{Bounds{Vector2{503.5, 414.5}, Vector2{25.5, 24.5}}, true},
    &Collider{Bounds{Vector2{592, 405}, Vector2{63, 36}}, true},
    &Collider{Bounds{Vector2{684, 390.5}, Vector2{29, 22.5}}, true},
    &Collider{Bounds{Vector2{764, 406.5}, Vector2{52, 38.5}}, true},
    &Collider{Bounds{Vector2{848, 417}, Vector2{33, 27}}, true},
    &Collider{Bounds{Vector2{944.5, 405}, Vector2{62.5, 37}}, true},
    &Collider{Bounds{Vector2{312, 71}, Vector2{23, 56}}, true},
    &Collider{Bounds{Vector2{630.5, 211.5}, Vector2{21.5, 6.5}}, true},
    &Collider{Bounds{Vector2{631.5, 235}, Vector2{7.5, 4}}, true},
    &Collider{Bounds{Vector2{247.5, 488.5}, Vector2{5.5, 3.5}}, true},
    &Collider{Bounds{Vector2{271, 510.5}, Vector2{13, 16.5}}, true},
    &Collider{Bounds{Vector2{279, 90.5}, Vector2{4, 13.5}}, true},
    &Collider{Bounds{Vector2{22, 92.5}, Vector2{5, 12.5}}, true},
    &Collider{Bounds{Vector2{246.5, 52}, Vector2{21.5, 5}}, true},
    &Collider{Bounds{Vector2{759, 57}, Vector2{38, 5}}, true},
    &Collider{Bounds{Vector2{806.5, 75.5}, Vector2{6.5, 2.5}}, true},
    &Collider{Bounds{Vector2{727.5, 91}, Vector2{7.5, 3}}, true},
    &Collider{Bounds{Vector2{949, 406.5}, Vector2{67, 37.5}}, true},
    &Collider{Bounds{Vector2{360, 220}, Vector2{7, 3}}, true},
    &Collider{Bounds{Vector2{263.5, 219}, Vector2{6.5, 4}}, true},
    &Collider{Bounds{Vector2{240.5, 406.5}, Vector2{48.5, 38.5}}, true}
  };

  std::vector<Collider*> colliders1_2{
    &Collider{Bounds{Vector2{422.5, 243.5}, Vector2{39.5, 11.5}}, true},
    &Collider{Bounds{Vector2{455.5, 264}, Vector2{6.5, 8}}, true},
    &Collider{Bounds{Vector2{536.5, 238.5}, Vector2{38.5, 16.5}}, true},
    &Collider{Bounds{Vector2{413, 223}, Vector2{34, 7}}, true},
    &Collider{Bounds{Vector2{536, 210.5}, Vector2{25, 7.5}}, true},
    &Collider{Bounds{Vector2{567.5, 195.5}, Vector2{7.5, 9.5}}, true},
    &Collider{Bounds{Vector2{543.5, 59}, Vector2{15.5, 4}}, true},
    &Collider{Bounds{Vector2{535, 265}, Vector2{7, 7}}, true}
  };

  NPC prisoner = make_prisoner(gm, prisoner_tex);

  Level* level1_1 = new Level{ "../resources/1-1.json" , &pc, std::vector<NPC*>{ &prisoner }, Bounds{Vector2{862.5, 52.5}, Vector2{19.5, 7.5}}, Bounds{Vector2{-2000, -2000}, Vector2{0, 0}}, colliders1_1 };
  Level* level1_2 = new Level{ "../resources/1-2.json" , &pc, std::vector<NPC*>{}, Bounds{Vector2{479, 55}, Vector2{14, 6}} ,Bounds{Vector2{480, 546.5}, Vector2{32, 10.5}}, colliders1_2 };
  Level* level1_3 = new Level{ "../resources/1-3.json" , &pc, std::vector<NPC*>{}, Bounds{Vector2{-2000, -2000}, Vector2{0, 0}} ,Bounds{Vector2{480, 546.5}, Vector2{32, 10.5}}, std::vector<Collider*>{} };

  Rectangle playable_are_1_1{ 12, 43, 1000, 520 };
  Rectangle playable_are_1_2{ 380, 43, 200, 520 };
  Rectangle playable_are_1_3{ 280, 43, 400, 520 };

  level1_1->set_playable_are(playable_are_1_1);
  level1_2->set_playable_are(playable_are_1_2);
  level1_3->set_playable_are(playable_are_1_3);
  pc.set_playable_area(playable_are_1_1);


  level1_1->set_next_room(level1_2);
  level1_2->set_previous_room(level1_1);
  level1_2->set_next_room(level1_3);
  level1_3->set_previous_room(level1_2);

  //level1_2->add_enemies(enemies);

  level1_1->set_exit_point(Vector2{ 851, 50 });
  level1_2->set_enter_point(Vector2{ 463, 456 });
  level1_2->set_exit_point(Vector2{ 490, 70 });
  level1_3->set_enter_point(Vector2{ 467, 430 });



  std::vector<Level*>levels{ level1_1, level1_2, level1_3 };

  Level* current_level{};

  current_level = levels[0];

  PlayerUI player_ui = PlayerUI{ pc };


  while (!window.ShouldClose()) // Detect window close button or ESC key
  {    

      if (current_level->exit_bounds.do_overlap(pc.player_collider->get_bounds()))
      {
          current_level = current_level->get_next_room();  
          Vector2 enter = current_level->get_enter_point();
          pc.set_playable_area(current_level->playable_area);

          pc.posn_ = enter;
          
      }

      if (current_level->enter_bounds.do_overlap(pc.player_collider->get_bounds()))
      {
          current_level = current_level->get_previous_room(); 
          Vector2 exit = current_level->get_exit_point();
          pc.set_playable_area(current_level->playable_area);

          pc.posn_ = exit;
          
      }


      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
          std::cout << GetMousePosition().x << " " << GetMousePosition().y << std::endl;
      }

    gm.update();
    current_level->update();
   
    BeginTextureMode(rt);

    ClearBackground(RAYWHITE);

    current_level->draw();

    player_ui.display();

    gm.draw(); // possibly draw the text box
    
    EndTextureMode();

    BeginDrawing();
    DrawTexturePro(
      rt.texture,
      Rectangle{ 0, 0, static_cast<float>(rt.texture.width), static_cast<float>(-rt.texture.height) },
      Rectangle{ 0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
      Vector2{ 0, 0 },
      0,
      WHITE);
    EndDrawing();
  }


  std::cout << "Waiting for the future's result to become available...\n";


  for (Level* level : levels) delete level;

  return 0;
}


aipfg::NPC make_reaper(aipfg::GameManager& gm, raylib::Texture& tex)
{
  using namespace aipfg;

  aipfg::Sprite s{ tex, 6, 1, { 60, 0 }};
  const std::string nature =
   "The following is a conversation with the grim reaper. The grim reaper is a "
   "personified force. In some mythologies, the grim reaper causes the "
   "victim's death by coming to collect that person's soul. In this instance,"
   "the reaper is healer who curses those who he heals."
   "\n\n";
  const std::string gambit = "You wish to risk death?";
  const std::string name   = "Reaper";

  return { gm, s, name, { nature, gambit } };
}

aipfg::NPC make_prisoner (aipfg::GameManager& gm, raylib::Texture& tex)
{
    using namespace aipfg;

    aipfg::Sprite s{ tex, 6, 1, { 146.5, 97.5 }, {{ "", { 3 } }} };
    const std::string nature =
        "The following is a conversation with rogue who survived the riots in the orc prison. The orcs run the prison to enslave humans. "
        "The rogue is still in prison cell too weak to escape"
        " The rogue is a resilient survivor with a sharp wit and keen observation skills. "
        "They are guarded and slow to trust, but fiercely loyal to those they hold dear. "
        "Despite their injuries and difficulty speaking, their irrepressible spirit and unbreakable will shine through. "
        "They must inform player of what happened here"
        "\n\n";
    const std::string gambit = "Who's there?";
    const std::string name = "The Rogue";

    return { gm, s, name, { nature, gambit } };
}

aipfg::NPC make_green_knight(aipfg::GameManager& gm, raylib::Texture& tex)
{
  using namespace aipfg;

  aipfg::Sprite s{ tex, 12, 8, { 400, 0 }, {{ "", { 10 } }} };
  std::string nature =
      "The following is a conversation with the green knight. The green knight is"
      "similar to the infamous black knight from Monty Python. He allows people"
      "to become more powerful by selling them special runes"
      "\n\n";
  const std::string name   = "Green Knight";
  const std::string gambit =
    "You wish to become more powerful?";
    // "I'll be glad to know. It's with him and no one else I'll hold a pact.";

  return { gm, s, name, { nature, gambit } };
}

aipfg::Enemy make_enemy(raylib::Texture& tex, Vector2 pos) {
    aipfg::Sprite s{ tex, 12, 8, pos, {{ "", { 8 } }} };
    return { s };
}