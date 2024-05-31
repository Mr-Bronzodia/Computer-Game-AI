#ifndef _TEXT_BOX_HPP_
#define _TEXT_BOX_HPP_

#include "game-manager.hpp"
#include "openai-helper.hpp"
#include "raylib-cpp.hpp"
#include <string>
#include <chrono>
#include <future>   // std async, std::future
#include <iostream>
#include <stdexcept> // std::runtime_error

namespace aipfg
{

// Provide this (TextBoxParams) as the user interface to creation of a TextBox
// NPC can then use its members to call the TextBox constructor below, while
// adding the stop_str parameter built from NPC::name Ideally we can also
// replace raylib::Window with GameManager, with it then having a
// raylib::Window member. But this will need moving inlined member functions
// into C++ classes to allow GameManager.hpp to be used in the code below.

struct TextBoxParams
{
  const std::string& nature_;
  const std::string& gambit_;
};

class TextBox
{
public:

  TextBox(GameManager&, const std::string&, const std::string&, const std::string&);

  TextBox(const TextBox& o);

  bool update();
  void update_prompt(const std::string& str);
  void draw();

  // OpenAI:
  std::string nature_{};
  std::string stop_str_{}; // = "Grim Reaper: ";
  std::string response_{};
  std::string prompt_{};
  std::future<void> response_future_{};

  GameManager& gm_;
  float max_text_width_;

  // static: Just one is used for all TextBox instances
  inline static const std::string human_stop_str_ = "Human: ";
  inline static const int font_size_ = 30;
  // n.b. "spacing" varies with the font & font size:
  inline static const float border_ = 20;

private:

  int nchars_entered_{};
  int tail_index_large_{}, tail_index_small_{};
  int* tail_index_{};

  std::string nature_prompt_{};

  Rectangle text_box_small_{};
  Rectangle text_box_large_{};
  Rectangle* text_box_{};

  const std::optional<std::vector<std::string>> stop_ = std::optional{std::vector{human_stop_str_, stop_str_}};
};

} // namespace aipfg

#endif // _TEXT_BOX_HPP_
