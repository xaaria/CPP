#include <iostream>
#include <string>
#include "rot13stream.h"

using namespace std;
using namespace otecpp_rot13stream;

int main() {

  //std::cout << otecpp_rot13stream::rot13( "ioweuweioQWERWFF##dfSFrkdashdh3hru2hSDFwefjwefejejejejd,,sdfsdeopioqweasdasdzcz" ) << std::endl;


  Rot13Stream r13s("Kokeillaan");
  cout << r13s.str() << endl;
  r13s.str("");
  r13s.clear();
  string mj("Ohjelmoinnin tekniikka");
  char c = 'C';
  int op = 5;
  r13s << mj << " " << c << "++ " << op << " op";
  string rot13 = r13s.str();
  cout << rot13 << endl;
  r13s.str("");
  r13s.clear();
  r13s << rot13;
  cout << r13s.str() << endl;

  return 0;
}