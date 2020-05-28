#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
// sanat.h

namespace otecpp_sanat {

  typedef std::map<std::string, unsigned int> mappi;
  typedef std::multimap<std::string, unsigned int> multimappi;

  multimappi rivit(std::istream &syote);
  multimappi tasmaavatRivit(std::istream& syote, std::set<std::string> sanat);
  mappi sanaLkmt(std::istream& syote);

  typedef std::map<std::string, std::vector<unsigned int> > rivivectori;
  rivivectori rivitTaulukkoon(const multimappi& rivimm);


}