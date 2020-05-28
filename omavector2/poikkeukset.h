/**
 * osa teht‰v‰‰: 4 - Oma vector #2
 * 
 * Esittelee oman poikkeusluokan joka perii standardikirjaston exception-luokan
 */ 
#ifndef POIKKEUKSET_H
  #define POIKKEUKSET_H

#include <iostream>
#include <exception>
#include <string>





namespace otecpp_poikkeukset {

  /**
   * Asettaa unexpected- ja terminate-k‰sittelijˆiksi funktiot ...
   */ 
  void asetaKasittelijat();

  /**
   * Suorittaa oman toimintalogiikan unexcepted():lle, joss asetaKasittelijat() on kutsuttu
   */ 
  void oma_unexpected();

  /**
   * Suorittaa oman toimintalogiikan terminate():lle, joss asetaKasittelijat() on kutsuttu
   */ 
  void oma_terminate();



  class OdottamatonPoikkeus : public std::exception {

    public:

      /**
       * Luo muotoa "Odottamaton poikkeus: <viesti>" olevan merkkijonon
       */ 
      OdottamatonPoikkeus(const std::string &viesti);

      virtual ~OdottamatonPoikkeus() throw();

      /**
       * Palauttaa rakentimessa as. merkkijonon vakio-C-merkkijonona
       * Peitt‰‰ luokan exception what() metodin
       */ 
      virtual const char* what() const throw();

    private:

      /**
       * Luokan j‰sen viesti jota k‰ytete‰‰n poikkeuksen tulostuksessa 
       */
      std::string viesti;


  };
  
}

#endif