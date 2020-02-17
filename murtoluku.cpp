#include <iostream>
#include <cmath>
#include <algorithm>
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

    /* 
      Supistaminen tapahtuu jakamalla sek‰ osoittaja ett‰ nimitt‰j‰ niiden suurimmalla yhteisell‰ tekij‰ll‰.
      T‰rke‰ huomio 2: Kun lasket suurinta yhteist‰ tekij‰‰, k‰sittele sek‰ osoittajaa ett‰ nimitt‰j‰‰ 
      positiivisena lukuna (eli k‰yt‰ niiden itseisarvoja).
    */

    // T‰rke‰ huomio 1: Jos joko osoittaja tai nimitt‰j‰ on 0, j‰t‰ luku supistamatta.
    // Siirr‰ t‰m‰ aivan ylˆs?
    if(this->nim == 0 || this->os == 0) { return; }

    // -- vain osoittajalla voi olla negatiivinen arvo
    if(this->nim < 0) {
      this->nim *= -1;
      this->os  *= -1;
    }

    

    int iso   = std::max( std::abs(this->nim), std::abs(this->os) );
    int pieni = std::min( std::abs(this->nim), std::abs(this->os) );

    while(iso != pieni) {
      iso -= pieni; // 1
      if(iso < pieni) {
        int tmp = iso;
        iso = pieni;
        pieni = tmp;
      }
    }

    // T‰ss‰ vaiheessa tied‰mme suurimman yht. tekij‰n. (= iso )
    this->os = this->os /   std::abs(iso);
    this->nim = this->nim / std::abs(iso);

  }


  /* osoittajaan joko lis‰t‰‰n tai siit‰ v‰hennet‰‰n nimitt‰j‰n arvo. Muista kutsua lopuksi funktiota sievenna */

  Murtoluku&  Murtoluku::operator++() {
    this->os += this->getNim();
    this->sievenna();
    return *this;
  }

  Murtoluku&  Murtoluku::operator--() {
    this->os -= this->getNim();
    this->sievenna();
    return *this;
  }

  /* 
    J‰lki-versiot: 
    Funktio m‰‰ritt‰‰ paikallisen Murtoluku-olion, joka on kopio oliosta itsest‰‰n (onnistuu esim. tapaan Murtoluku ml(*this)). 
    T‰m‰n j‰lkeen olion itsens‰ kuvaamaa arvoa kasvatetaan yhdell‰ (ja tarvittaessa kutsutaan funktiota sievenna). 
  */

  Murtoluku   Murtoluku::operator++(int) {
    Murtoluku ml(*this);
    this->os += this->getNim();
    this->sievenna();
    return ml;
  }

  Murtoluku   Murtoluku::operator--(int) {
    Murtoluku ml(*this);
    this->os -= this->getNim();
    this->sievenna();
    return ml;
  }



  /*
    Kerrotaan ritiin kukin luku nimitt‰jill‰, lasketaan yhteen ja sievennet‰‰n (rakennin hoitaa).
  */
  Murtoluku operator+(const Murtoluku &a, const Murtoluku &b) {

    return Murtoluku(
      a.getOs() * b.getNim() + b.getOs() * a.getNim(),
      a.getNim() * b.getNim()
    );  
  }
  Murtoluku operator-(const Murtoluku &a, const Murtoluku &b) {
    return Murtoluku(
      a.getOs() * b.getNim() - b.getOs() * a.getNim(),
      a.getNim() * b.getNim()
    );  
  }
  
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
      b.getOs()  *  a.getNim()
    );
  }

  std::ostream& operator<<(std::ostream &virta, const Murtoluku &ml) {

    // Jos sek‰ osoittaja ett‰ nimitt‰j‰ ovat erisuuria kuin 0 ja lis‰ksi nimitt‰j‰ on erisuuri kuin 1,
    // tulostetaan luku tulostevirtaan virta muodossa osoittaja/nimitt‰j‰.
    if(ml.getOs() != 0 && ml.getNim() != 0 && ml.getNim() != 1) {
      virta << ml.getOs() << "/" << ml.getNim(); 
    }
    // Jos osoittaja on erisuuri kuin 0 ja nimitt‰j‰ on 1, tulostetaan pelkk‰ osoittaja (koska kyseess‰ on kokonaisluku).
    else if(ml.getOs() != 0 && ml.getNim() == 1) {
      virta << ml.getOs();
    }
    // Jos osoittaja on 0, tulostetaan luku yksinkertaisesti muodossa 0.
    else if(ml.getOs() == 0) {
      virta << 0;
    }
    // Jos nimitt‰j‰ on 0 (ja osoittaja ei ole 0), tulostetaan joko merkkijono "-inf" tai "inf", 
    // riippuen siit‰ onko osoittaja negatiivinen vai positiivinen
    else if( ml.getNim() == 0 && ml.getOs() != 0 ) {
      if(ml.getOs() < 0) {
        virta << "-";
      }
      virta << "inf";
    }


    return virta;
  }


}