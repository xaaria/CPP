/**
 * osa teht‰v‰‰: 4 - Oma vector #2
 * Poikkeukset.h:n toteutustiedosto
 */ 
#include "poikkeukset.h"
#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <sstream>


namespace otecpp_poikkeukset {



  void oma_unexpected() {

    try {
      throw;    /* "Heitt‰‰ poik. eteenp‰in" */
    }
    catch(int i) {
      
      std::string str;         
      std::ostringstream temp; 
      temp << i;
      throw OdottamatonPoikkeus( "int " + temp.str() );

    } 
    catch(...) {
      /* ... = mik‰ tahansa poikkeus */
      std::cout << "Ohjelma lopetetaan odottamattoman poikkeuksen vuoksi" << std::endl;
      std::terminate();  /* jonka pit‰isi kutsua erikseen as. funktiota */
    }

  }


  void oma_terminate() {
    std::cout << "Kutsuttiin omaa terminate-funktiota" << std::endl;
    exit(EXIT_SUCCESS);
  }


  void asetaKasittelijat() {
    std::set_unexpected(oma_unexpected);
    std::set_terminate(oma_terminate);
  }


  /* -- Luokka -- */

  OdottamatonPoikkeus::OdottamatonPoikkeus(const std::string &viesti_) : viesti(viesti_) {
    this->viesti = "Odottamaton poikkeus: " + this->viesti;
  }


  OdottamatonPoikkeus::~OdottamatonPoikkeus() throw() {}

  const char* OdottamatonPoikkeus::what() const throw() {
    return this->viesti.c_str();
  }


}