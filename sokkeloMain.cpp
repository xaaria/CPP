// sokkeloMain.cpp
#include <fstream>
#include <iostream>
#include <stack>
#include <utility>  // pair
#include <signal.h>
#include "sokkelo.h"

using namespace std;
using otecpp_sokkelo::Sokkelo;

/*
void signal_callback_handler(int signum) {
  printf("Caught signal %d\n",signum);
}
*/



int main() {

  //signal(SIGINT, signal_callback_handler);

  ifstream td("sokkelo3.txt");
  
  Sokkelo s(td);
  long i = 0;
  bool x = true;

  while(x) {
    //std::cout << i+1 << ") Liike alkaa --\n";
    cout << "ASKEL#" << i++ << endl;
    
    try {
      x = s.askella( 3 );
    } catch (const std::exception &ex) {
      cout << ex.what();
    }
    //cout << "askella palautti " << x << " pino: " << s.pino().size() << endl;
    
    if(i > 870) {
      cout << s << '\n';
    }

    if(!x) {
      break;
    } 
  }

  td.close();
  std::cout << "END, SUCCESS";
  return 0;
 
}