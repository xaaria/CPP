#include <iostream>
#include <vector>
#include <string>
// tyypit.h

namespace otecpp_tyypit {

  struct Tyypit {
    std::vector<long int>     kokonaisluvut;
    std::vector<double>       liukuluvut;
    std::vector<bool>         totuusarvot;
    std::vector<std::string>  muut;
  };


  Tyypit keraaTyypit(std::istream &virta);



}