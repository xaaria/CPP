#include <iostream>
#include <sstream>
#include <string>
#include "rot13stream.h"
// rot13stream.cpp

namespace otecpp_rot13stream { 


  // Rakennin
  Rot13Stream::Rot13Stream(const std::string& s) : std::ostringstream( rot13(s) ) {
    // ...
  }

  // 1
  Rot13Stream& Rot13Stream::operator<<(char c) {
    std::ostringstream& oss = *this;
    oss << rot13( std::string(1, c) );
    return *this;
  }

  // 2
  Rot13Stream& Rot13Stream::operator<<(const std::string& s) {
    std::ostringstream& oss = *this;
    oss << rot13(s);
    return *this;
  }

  // 3
  Rot13Stream& Rot13Stream::operator<<(const char* s) {
    std::ostringstream& oss = *this;
    oss << rot13( std::string(s) );
    return *this;
  }

  // 4
  Rot13Stream& Rot13Stream::operator<<(int i) {
    std::ostringstream& oss = *this;
    oss << i;
    return *this;
  }







  /* Ottaa parametriksi merkkijonon s ja palauttaa uuden string-olion rot13 koodattuna */
  std::string rot13(const std::string s) {

    std::string rot("");

    for(std::string::size_type ci = 0; ci < s.length(); ++ci) {
      rot += rot13( s.at(ci) );
    }
    return rot;

  }



  /*
    Muuntaa parametrina saadun charin c vast. rot 13 -chariksi
    tai palauttaa merkin sellaisenaan, jos ei muunnettavissa (esim. välilyönti)
  */
  char rot13(const char c) {
    
    const int rot_max = 26; // n. kirjain jonka jalkeen alkaa alusta [Ei indeksi!]
    std::string chr_lc = "abcdefghijklmnopqrstuvwxyz"; // len 26
    std::string chr_uc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // uusi indeksi ja sen paikka
    int pos = -1;

    if(isupper(c) != 0) {
      pos = chr_uc.find(c);
    } else {
      pos = chr_lc.find(c);
    }

    if(pos != std::string::npos) {
      // Laske uuden merkin indeksi
      unsigned int new_i = (pos+13) % rot_max;
      if(isupper(c) != 0) {
        return chr_uc.at(new_i);
      } else {
        return chr_lc.at(new_i);
      }
    }
    else {
      return c; // palauta merkki takaisin jos NPOS
    }


  }

}