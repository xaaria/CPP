#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <utility>
#include <map>
#include "sanat.h"
// sanat.cpp

namespace otecpp_sanat {


  /*
    lukee sy�tevirtaa syote rivi kerrallaan niin kauan kuin luku onnistuu, 
    ja lis�� jokaisen luetussa riviss� esiintyv�n sanan kohdalla 
    multimap<string, unsigned int>-olioon avain-alkioparin, 
    jonka avain on kyseinen sana ja alkio on kyseisen sanan 
    sis�lt�neen rivin j�rjestysnumero sy�tteess�. 

    TODO: RIVIN j�rjestysnumero! Sama logiikka my�s seuraavalle!
  */
  multimappi rivit(std::istream& syote) {

    multimappi sanat;
    unsigned int row_ord = 1;

    std::string line;
    while( std::getline(syote, line) ) {

      std::string x = "";
      std::stringstream ss(line);

      

      while(!ss.fail()) {
        
        ss >> x; // yrit� lukea sana
        if(ss.fail()) { break; }

        sanat.insert( std::make_pair( x, row_ord) );
        //std::cout << "Add: " << x << "," <<  row_ord << "\n";
      }
      ++row_ord;
      

    }
    return sanat;

  }


  /*
    Sama kuin rivit(), mutta nyt niin, ett� vain ne sanat, jotka esiintyv�t
    joukossa sanat, tallennetaan
  */
  multimappi tasmaavatRivit(std::istream& syote, std::set<std::string> sanat_) {

    multimappi sanat;
    unsigned int row_ord = 1;

    std::string line;
    while( std::getline(syote, line) ) {

      std::string x = "";
      std::stringstream ss(line);

      while(!ss.fail()) {
        
        ss >> x; // yrit� lukea sana
        if(ss.fail()) { break; }

        if( sanat_.find(x) != sanat_.end() ) {
          sanat.insert( std::make_pair( x, row_ord) );
          //std::cout << "Add: " << x << "," <<  row_ord << "\n";
        }
      }
      ++row_ord;
      

    }
    return sanat;


  }

  /* Laskee kunkin sanan esiintymisen */
  mappi sanaLkmt(std::istream& syote) {

    mappi lkm;

    while(true) {
      std::string sana = "";
      syote >> sana;

      if(syote.fail()) { break; }

      if( lkm.find(sana) != lkm.end() ) {
        lkm.find(sana)->second += 1;
      } else {
        lkm.insert( std::make_pair(sana, 1) );
      }
      
    }
    return lkm;

  }

 
  /*
    Muuttaa multimapin <{sana:1}, {sana,2}> muotoon <{sana: vec(1,2,...)}, ...>
  */
  rivivectori rivitTaulukkoon(const multimappi& rivimm) {

    rivivectori riviVec;

    for(multimappi::const_iterator it=rivimm.begin(); it != rivimm.end(); ++it) {
      
      // Jos sana ei ole riviveciss�, lis�� sinne avain kys. sanalla ja vektori jonka 1. arvo on kys. rivi.
      // riviVec:
      //  'sana' => vector(1,2,....)

      // jos EI ole avainta 'sana': lis�� se, ja vektori jossa kys. rivinro
      if(riviVec.find(it->first) == riviVec.end()) {
        riviVec.insert(
          std::make_pair( it->first, std::vector<unsigned int>(1, it->second))
        );
        //std::cout << "+ " << it->first << "|" << it->second << " \n";
      } else {
        // Muutoin: ota riviVecin alkio av. 'sana', laita sen vektoriin (->second) kys. rivinro
        riviVec.find(it->first)->second.push_back(it->second); 
        //std::cout << "\t Avain on jo, lis�t��n arvo: " << it->second << "\n"; 
      }

    }

    return riviVec;

  }




  
}