#include <iostream>
#include <sstream>
#include <string>
#include "tyypit.h"
// tyypit.cpp

namespace otecpp_tyypit {

  otecpp_tyypit::Tyypit keraaTyypit(std::istream& virta) {

    std::string inp = "";
    long int a = 0;
    double b = 0.0; 
    bool c;
    char x;

    virta >> inp;

    std::istringstream ss_(inp);
    //ss_ >> std::boolalpha;

    /*
      -- yrittämällä lukea istringstream-oliosta heti perään vielä yksi char-merkki. 
      Jos tämä luku onnistuu, ei sana kokonaisuudessaan esittänyt haluttua tyyppiä
    */

    ss_ >> a;
    if( !ss_.fail()) {
      ss_.clear();
      ss_.get();
      if( ss_.fail() ) {  
        std::cout << " kokonaisluku " << a << "\n";
      }
    }

    ss_.clear();

    ss_ >> b; // try to convert
    if( !ss_.fail() ) {
      ss_.clear();
      ss_.get();
      if( ss_.fail() ) {  
        std::cout << " liukuluku (double OR int) " << b << std::endl;
      }
    }

    ss_.clear();

    ss_ >> std::boolalpha >> c; // try to convert. Use boolapha
    if( !ss_.fail() ) {
      ss_.clear();
      ss_.get();
      if( ss_.fail() ) {
        std::cout << " bool\n";
      }
    }

  }

}



int main() {

  otecpp_tyypit::keraaTyypit( std::cin );
  
}