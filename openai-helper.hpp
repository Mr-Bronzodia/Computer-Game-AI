#ifndef _OPENAI_HELPER_HPP_
#define _OPENAI_HELPER_HPP_

#include <string>
#include <optional>
#include <vector>

namespace liboai
{
  class OpenAI;
}

namespace aipfg
{

class openai_helper
{
public:
  openai_helper();
  ~openai_helper();

  void submit(const std::string& prompt, std::string& response_str,
              const std::optional<std::vector<std::string>>& stop = std::nullopt);

  bool reapHeal = false;
  bool upgrHP = false;
  bool upgrDmg = false;
  bool upgrShl = false;
  bool upgrSpd = false;

private:
  liboai::OpenAI* oai_;
  
};

} // namespace aipfg

#endif // _OPENAI_HELPER_HPP_
