#include <string>
#include <vector>
#include <set>

// hirsipuu.h

namespace otecpp_hirsipuu {

  void hirsipuu(const std::string& sanatiedosto, unsigned int x, unsigned int maxVirheet);
  

  std::vector<std::string> haeSanatTiedostosta(const std::string& sanatiedosto);
  bool onkoKirjainSanassa(const char kirjain, const std::string sana);
  std::string haeSananTilanne(const std::string& sana, const std::set<char>& arvaukset);
  void haeLopetusviesti(const std::string& sana, const bool victory=false);

}