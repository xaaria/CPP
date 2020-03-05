#include <string.h>
#include "poikkeukset.h"
// poikkeukset.cpp

namespace otecpp_poikkeukset {

  LaitonIndeksi::LaitonIndeksi(const std::string& msg_) : msg(msg_) {
  }
  
  LaitonIndeksi::~LaitonIndeksi() throw() {
    // ...
  }
  
  const char* LaitonIndeksi::what() const throw() {
    std::string x("Laiton indeksi: ");
    x += this->msg;
    return x.c_str();
  }

}
