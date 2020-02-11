#include <iostream>
#include <string>
#include "ruudut.h"
// ruudut.cpp


namespace otecpp_ruudut {

  void piirraRuutuja(std::istream &syote, std::ostream &tuloste) {

    // If syote ok
    if(syote) {
      std::string input = "";
      while(std::getline(syote, input)) {
        
        char c_cmd[100];
        std::string cmd;
        int x, y;
        char c;
        
        // Read 3 params. if read 3, everything ok
        if(sscanf( input.c_str(), "%s %u %u %c", &c_cmd, &x, &y, &c) == 4) {
          //cmd = c_cmd; // C styled string to c++ string
        }
        else if(sscanf( input.c_str(), "%s %u %u", &c_cmd, &x, &y) == 3) {
          //cmd = c_cmd; // C styled string to c++ string
        }
        else if(sscanf( input.c_str(), "%s", &c_cmd) == 1) {
          //cmd = c_cmd;
        }
        else {
          tuloste << "Laiton komento!\n\n";
        }

        // Command format ok, just check that x and y are > 0
        cmd = c_cmd;
        if(cmd == "lopeta") {
          return;
        }

        

      }
    }

    return;
  }

}




int main() {


  otecpp_ruudut::piirraRuutuja(std::cin, std::cout);


  return 0;

}