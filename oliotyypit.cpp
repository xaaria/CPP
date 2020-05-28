#include <iostream>
#include <vector>
#include <typeinfo>
#include "luvut.h" /* !! */
#include "oliotyypit.h"


namespace otecpp_oliotyypit {

  void laskeLuvut(const std::vector<otecpp_luvut::Luku*> luvut) {

    unsigned int ml = 0;
    unsigned int kl = 0;
    unsigned int ll = 0; // murto-, kokonais-, liukuluku

    for(std::vector<otecpp_luvut::Luku*>::size_type i=0; i<luvut.size(); ++i) {
      
      otecpp_luvut::Luku* luku_ = luvut.at(i);

      // Yritetään muuntaa Luku pointteri Murtoluku POINTTERIKSI (!!)
      if( dynamic_cast<otecpp_luvut::Murtoluku*>(luku_) != NULL ) {
        ++ml;
        continue;
      }
      else if( dynamic_cast<otecpp_luvut::Kokonaisluku*>(luku_) != NULL ) {
        ++kl;
        continue;
      }
      else if( dynamic_cast<otecpp_luvut::Liukuluku*>(luku_) != NULL ) {
        ++ll;
        continue;
      } 
      else {
        // ???
      }

    }

    std::cout << "Kokonaisluku: " << kl << " kpl" << std::endl;
    std::cout << "Liukuluku: " << ll << " kpl" << std::endl;
    std::cout << "Murtoluku: " << ml << " kpl" << std::endl;

  }


}