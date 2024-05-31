#include "text-box.hpp"
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

TextBox::TextBox(GameManager& gm, const std::string& nature,
                 const std::string& gambit, const std::string& stop_str)
  : nature_{ nature }, gm_{ gm }, stop_str_{ stop_str },
    tail_index_{ &tail_index_small_ }, text_box_{ &text_box_small_ }
{
  static const std::string new_lines = "\n\n\n\n\n\n\n\n\n"; // 9
  prompt_ = new_lines + stop_str_ + gambit + '\n' + human_stop_str_;

  const float jump_fix = 4;
  const float box_width = (float)gm.window_.GetWidth() - (2 * border_);
  const float box_ypos = (float)gm.window_.GetHeight() - 200;
  const float box_height_small = (float)gm.window_.GetHeight() - box_ypos - border_;
  const float box_height_large = (float)gm.window_.GetHeight() - (2 * border_) + jump_fix;
  text_box_small_ = { border_, box_ypos, box_width, box_height_small };
  text_box_large_ = { border_, border_ - jump_fix,   box_width, box_height_large };

  const float average_word_size = MeasureText("Abcdefg", font_size_);
  max_text_width_ = box_width - average_word_size;
  tail_index_small_ = prompt_.rfind('\n');
  tail_index_small_ = prompt_.rfind('\n', tail_index_small_ - 1);
}

TextBox::TextBox(const TextBox& o) :
  nature_{ o.nature_ },
  stop_str_{ o.stop_str_ },
  response_{ o.response_ },
  prompt_{ o.prompt_ },
  gm_{ o.gm_ },
  max_text_width_{ o.max_text_width_ },
  nchars_entered_{ o.nchars_entered_ },
  tail_index_large_{ o.tail_index_large_ },
  tail_index_small_{ o.tail_index_small_ },
  tail_index_{ &tail_index_small_ },
  nature_prompt_{ o.nature_prompt_ },
  text_box_small_{ o.text_box_small_ },
  text_box_large_{ o.text_box_large_ },
  text_box_{ &text_box_small_ }
{
  if (o.response_future_.valid())
  {
    auto text = "std::future has no copy constructor."
                "We can only handle the member when in an invalid state.";
    throw std::runtime_error{ text };
  }
}

bool TextBox::update()
{
  bool keep_updating{ true }; // return value
  bool waiting{ response_future_.valid() };

  if (waiting &&
      std::future_status::ready ==
      response_future_.wait_for(std::chrono::seconds(0)))
  {
    response_future_.get(); // invalidates the future
    for (auto& c : response_)
    {
      c = (c=='\n') ? ' ' : c; // replace newlines with spaces
    }
    response_ += '\n' + human_stop_str_;
    update_prompt(response_);
    nchars_entered_ = 0;
  }

  switch (GetKeyPressed())
  {
    case KEY_ESCAPE:
      if (text_box_ == &text_box_large_) // esc resumes the small text box
      {
        text_box_ = &text_box_small_;
        tail_index_ = &tail_index_small_;
      }
      else
      {
        SetExitKey(KEY_ESCAPE);
        keep_updating = false;
      }
      break;

    case KEY_ENTER:
      {
      if (waiting)
      {
        break;
      }
      update_prompt('\n' + stop_str_);
      nature_prompt_ = nature_ + prompt_;
      response_future_ =
        std::async(std::launch::async, &openai_helper::submit, &gm_.oai_help_,
                   std::cref(nature_prompt_), std::ref(response_),
                   std::cref(stop_));
      }
      break;

    case KEY_UP:
      text_box_ = &text_box_large_;
      tail_index_ = &tail_index_large_;
      break;

    case KEY_BACKSPACE:
      if (waiting)
      {
        break;
      }
      if (nchars_entered_ > 0)
      {
        bool reposition = prompt_.back() == '\n'; // last char is newline
        prompt_.pop_back();
        nchars_entered_--;
        if (reposition)
        {
          tail_index_large_ = prompt_.rfind('\n', tail_index_large_ - 2) + 1;
          tail_index_small_ = prompt_.rfind('\n', tail_index_small_ - 2) + 1;
        }
      }
      break;
  }

  while (int key = GetCharPressed())
  {
    if (waiting)
    {
      continue;
    }
    if ((key >= 32) && (key <= 125)) // e.g. don't grab the ESC key
    {
      update_prompt(std::string{(char)key});
    }
  }

  return keep_updating;
}

void TextBox::update_prompt(const std::string& str)
{
  for (char c : str)
  {
    const char* psz = &prompt_[prompt_.rfind('\n') + 1];

    if (c == ' ' && MeasureText(psz, font_size_) > max_text_width_)
    {
      c = '\n';
    }

    if (c == '\n')
    {
      tail_index_large_ = prompt_.find('\n', tail_index_large_) + 1;
      tail_index_small_ = prompt_.find('\n', tail_index_small_) + 1;
    }

    prompt_.push_back(c);
    nchars_entered_++;
  }
}

void TextBox::draw()
{
  Color light_gray_transparent{ 80, 80, 80, 192 }; // 192/256 nontransparent
  DrawRectangleRec(*text_box_, light_gray_transparent);
  unsigned int milliseconds = (unsigned int)(GetTime() * 1000.0);
  std::string s = &prompt_[*tail_index_];
  if ((milliseconds % 1000) > 500)
  {
    s.push_back('_');
  }
  DrawText(s.c_str(), (*text_box_).x + 12, (*text_box_).y + 12, font_size_, WHITE);
}

} // namespace aipfg
