#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
// mediaani.h

namespace otecpp_mediaani {

  /* int ja liukuluvut? */
  template<typename T> T mediaani(const std::vector<T> &taulu) {

    std::vector<T> taulu_kopio = taulu;
    std::sort(taulu_kopio.begin(), taulu_kopio.end());

    if(taulu_kopio.size() % 2 == 1) {
      // palauta keskim.
      return taulu_kopio[ taulu_kopio.size()/2 ];
    } 
    else {
      return (taulu_kopio[ (taulu_kopio.size()/2)-1 ] + taulu_kopio[ taulu_kopio.size()/2 ]) /2;
    }
  }

  /*
    Parillinen alkioiden lukum‰‰r‰ kuitenkin tuottaa ongelmia, 
    koska yll‰ kuvattua kahden keskimm‰isen alkion keskiarvoa ei voi 
    sellaisenaan laskea kahdelle merkkijonolle. 
    --
    1) Alkuun asetetaan merkkijonojen a ja b ns. pisin yhteinen etuliite eli sellainen alkuosa, 
    joka on sama sek‰ merkkijonossa a ett‰ b.

    2) -- ensimm‰isen ei-t‰sm‰‰v‰n merkkiparin char-arvojen keskiarvo.
    Jos jommassa kummassa merkkijonossa ei en‰‰ ole seuraavaa merkki‰, k‰ytet‰‰n puuttuvan merkin tilalla arvoa 0.

  */
  std::string mediaani(const std::vector<std::string> &taulu) {

    std::vector<std::string> taulu_kopio = taulu;
    std::sort(taulu_kopio.begin(), taulu_kopio.end());

    // JOS taulussa pariton m‰‰r‰, palauta vain keskimm‰inen normaalisti
    if( taulu_kopio.size() % 2 == 1 ) {
      return taulu_kopio.at( taulu_kopio.size()/2 );
    }
    // else:
    
    std::string med("");
    std::string a = taulu_kopio.at( (taulu_kopio.size()/2)-1 );
    std::string b = taulu_kopio.at( taulu_kopio.size()/2 );

    // Sovitaan, ett‰ a on pidempi
    if(a.size() < b.size()) {
      std::string temp = a;
      a = b;
      b = temp;
    }

    // Etsi 1. ei-t‰sm‰‰v‰t merkit (charit)
    for(unsigned int ci=0; ci < a.size(); ++ci) {

      // jos ci on jo enem‰n kuin b:ss‰ indeksej‰ 
      if( ci >= b.size()) {
        med += a.at(ci) / 2; // keskiarvon toinen j‰sen on 0 (huom: ei char '0'), siten myˆs j‰tetty pois
        break; // lopeta suoritus
      }
      else if( a.at(ci) != b.at(ci) ) {
        med += (a.at(ci) + b.at(ci)) / 2; // charien keskiarvo
        break; // lopeta suoritus
      } 
      else {
        med += a.at(ci); // lis‰‰ merkki merkkijonon per‰‰n
      }

    }

    return med;

  }


}