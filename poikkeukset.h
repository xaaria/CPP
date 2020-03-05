#ifndef POIKKEUKSET_H
  #define POIKKEUKSET_H

#include <exception>
#include <iostream>
#include <string>
// poikkeukset.h

/*
  Luokalla exception on yksi virtuaalifunktio:
  const char* what() const throw()
  - kalvot s. 158

  Tutoriaali: http://www.cplusplus.com/doc/tutorial/exceptions/
*/

namespace otecpp_poikkeukset {

  class LaitonIndeksi : public std::exception {

    private:
      std::string msg;

    public: 
      LaitonIndeksi(const std::string& msg = ""); // const.
      
      
      virtual ~LaitonIndeksi() throw();

      // throw m‰‰r. per‰ss‰ kertoo, mit‰ poikkeuksia kys. funktio heitt‰‰
      // () tarkotitaa tyhj‰‰
      // huomaa C-merkkijono!
      const char* what() const throw(); 
  
  };


}
#endif