#include <iostream>
#include <cmath>
#include "murtoluku.h"

// murtoluku.cpp

namespace otecpp_murtoluku {

  // Luo Murtoluku-olion ja sievent‰‰ sen!
  Murtoluku::Murtoluku(int os, int nim) : os(os), nim(nim) {
    this->sievenna();
  }

  // Getterit
  int Murtoluku::getOs()  const   { return this->os; }
  int Murtoluku::getNim() const   { return this->nim; }
  void Murtoluku::setOs(int os)    { this->os = os; }
  void Murtoluku::setNim(int nim)  { this->nim = nim; }

  void Murtoluku::sievenna() {
    // -- vain osoittajalla voi olla negatiivinen arvo
    if(this->nim < 0) {
      this->nim *= -1;
      this->os  *= -1;
    }
  }


  /* osoittajaan joko lis‰t‰‰n tai siit‰ v‰hennet‰‰n nimitt‰j‰n arvo. Muista kutsua lopuksi funktiota sievenna */

  Murtoluku&  Murtoluku::operator++() {
    this->os += this->nim;
    this->sievenna();
  }
  Murtoluku&  Murtoluku::operator--() {
    this->os -= nim;
    this->sievenna();
  }

  /* 
    J‰lki-versiot: 
    Funktio m‰‰ritt‰‰ paikallisen Murtoluku-olion, joka on kopio oliosta itsest‰‰n (onnistuu esim. tapaan Murtoluku ml(*this)). 
    T‰m‰n j‰lkeen olion itsens‰ kuvaamaa arvoa kasvatetaan yhdell‰ (ja tarvittaessa kutsutaan funktiota sievenna). 
  */

  Murtoluku   Murtoluku::operator++(int) {
    Murtoluku ml = Murtoluku(*this);
    return ml++;
  }
  Murtoluku   Murtoluku::operator--(int) {
    Murtoluku ml = Murtoluku(*this);
    return ml--;
  }




  Murtoluku operator+(const Murtoluku &a, const Murtoluku &b) {
    
  }
  Murtoluku operator-(const Murtoluku &a, const Murtoluku &b);
  
  Murtoluku operator*(const Murtoluku &a, const Murtoluku &b) {
    // kerro os. ja nim kesken‰‰n
    return Murtoluku( 
      a.getOs()   * b.getOs(), 
      a.getNim()  * b.getNim()
    );
  }

  Murtoluku operator/(const Murtoluku &a, const Murtoluku &b) {
    // Jakolasku on kertolasku k‰‰nteisluvulla (ja sama toisinp‰in)
    return Murtoluku( 
      a.getOs()   * b.getNim(), 
      a.getNim()  * b.getOs()
    );
  }

  std::ostream& operator<<(std::ostream &virta, const Murtoluku &ml) {
    virta << ml;
    return virta;
  }


}