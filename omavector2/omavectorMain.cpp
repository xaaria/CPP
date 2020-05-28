/**
 * Tehtävän 4 - omavector #2 main-tiedosto
 * ÄLÄ MUOKKAA
 */ 
#include <iostream>
#include <stdexcept>
#include "otevector.h"
#include "poikkeukset.h"

using namespace std;
using otecpp_otevector::OteVector;
using otecpp_poikkeukset::asetaKasittelijat;
using otecpp_poikkeukset::OdottamatonPoikkeus;

namespace  // Alla sisäisesti linkittyvä apufunktio (nimetön nimiavaruus).
{
  void luoPoikkeus(OteVector<int> &t, int k)
          throw(out_of_range, OdottamatonPoikkeus) {
    if(k == 0) {
      t[4] = 10;      // Laiton indeksi 4: lailliset indeksit ovat 0...3.
    }
    else if(k == 1) {
      cout << t[-2];  // Laiton indeksi -2.
    }
    else if(k == 2) {
      throw -500;     // Heitetään int-poikkeus -500.
    }
    else {
      throw 9.5;      // Heitetään double-poikkeus.
    }
  }
}

int main() {
  OteVector<int> t(4);
  asetaKasittelijat();  // Kutsutaan toteuttamaasi funktiota.
  for(int kierros = 0; kierros < 4; ++kierros) {
    try {
      luoPoikkeus(t, kierros);
    }
    catch(out_of_range &e) {
      cout << e.what() << '\n';
    }
    catch(OdottamatonPoikkeus &e) {
      cout << e.what() << '\n';
    }
  }
}