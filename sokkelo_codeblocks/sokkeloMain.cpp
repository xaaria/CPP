// sokkeloMain.cpp
#include <fstream>
#include <iostream>
#include <stack>
#include <utility>  // pair
#include "sokkelo.h"

using namespace std;
using otecpp_sokkelo::Sokkelo;


int main() {

  ifstream td("sokkelo3.txt");
  
  Sokkelo s(td);
  long i = 0;

  while(true) {
    //std::cout << i+1 << ") Liike alkaa --\n";
    cout << "ASKEL#" << i++ << endl;
    bool x = s.askella( 1 );
    //cout << "askella palautti " << x << " pino: " << s.pino().size() << endl;
    
    cout << s << '\n';

    if(!x) {
      break;
    } 
  }

  td.close();
  std::cout << "END, SUCCESS";
  return 0;
 
}