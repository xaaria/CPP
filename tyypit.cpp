#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include "tyypit.h"
// tyypit.cpp -- Tyyppien luku

const bool DEBUG = true;

namespace otecpp_tyypit {

  otecpp_tyypit::Tyypit keraaTyypit(std::istream& virta) {

    std::string inp   = "";
    std::string word  = "";
    long int a = 0;
    double b = 0.0; 
    bool c;
    Tyypit luokittelu; 


    /*
      -- yrittämällä lukea istringstream-oliosta heti perään vielä yksi char-merkki. 
      Jos tämä luku onnistuu, ei sana kokonaisuudessaan esittänyt haluttua tyyppiä
    */

    while( virta >> word ) {

      std::istringstream ss_(word);

      ss_ >> a;
      if( !ss_.fail()) {
        ss_.clear();
        ss_.get();
        if( ss_.fail() ) {  
          if(DEBUG)
            std::cout << "kokonaisluku " << a << "\n";
          luokittelu.kokonaisluvut.push_back(a);
          continue;
        }
      }

      ss_.str(word);
      ss_.clear();

      ss_ >> b; // try to convert
      if( !ss_.fail() ) {
        if(DEBUG) {
          std::cout << "-- luettiin: "<< b << std::endl;
        }
        ss_.clear();
        ss_.get();
        if( ss_.fail() ) {  
          if(DEBUG)
            std::cout << "liukuluku (double OR int) " << b << std::endl;
          luokittelu.liukuluvut.push_back(b);
          continue;
        }
      }

      ss_.str(word);
      ss_.clear();

      ss_ >> std::boolalpha >> c; // try to convert. Use boolapha
      if( !ss_.fail() ) {
        ss_.clear();
        ss_.get();
        if( ss_.fail() ) {
          if(DEBUG)
            std::cout << "bool\n";
          luokittelu.totuusarvot.push_back(c);
          continue;
        }
      }

      if(DEBUG)
        std::cout << "muu!\n";
      luokittelu.muut.push_back(word);

    }

    // Lopuksi, palauta
    return luokittelu;

  }

}



int main() {

  if(DEBUG) {
    otecpp_tyypit::Tyypit t = otecpp_tyypit::keraaTyypit( std::cin );
  }
  
}