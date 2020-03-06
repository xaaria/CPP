#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <utility>
#include "sokkelo.h"

// sokkelo.cpp

namespace otecpp_sokkelo {

  /* Lukee sokkeloruudukon syötevirrasta in */
  Sokkelo::Sokkelo(std::istream& in) {

    this->suunta = OIK;

    unsigned int r = 0; // rivi
    char line[100];

    while( in.getline(line, 100, '\n') ) {
      
      // lisää tyhjä char-rivi sokkelon rakenteeseen
      this->sokkelo.push_back( std::vector<char>() );
      //std::cout << line << "\n";
      std::stringstream ss(line);
      ss << std::noskipws; // älä skippaa valkomerkkejä (välil.)
      char c;

      while(ss >> c) {
        this->sokkelo.at(r).push_back( c ); 
      }
      ++r; // kasvata riviä

    }

  }

  /*
    Suorittaa liikkumisen [ohjeen kohdan 3] hakuaskeleen x kertaa (jos mahdollista).
    Eli palautetaan FALSE, jos joko löydettiin reitti ulos sokkelosta tai hakupino tuli tyhjäksi.
  */
  bool Sokkelo::askella(unsigned int x) {

    // Triviaali tarkastus A
    if(this->onkoReunalla()) { return false; }

    // Suorita X kertaa, tai poistu kesken pois jos ei mahd.
    for(unsigned int kerta=0; kerta<x; ++kerta ) {

      // Yritä ensin oik.
      Yritys y = OIK_;
      if(getRuudunTyyppi(getUusiSijainti(y)) == VAPAA) {
        std::cout << "voidaan liikkua OIK\n";
        continue;
      }
      if(getRuudunTyyppi(getUusiSijainti(SUOR_)) == VAPAA) {
        std::cout << "voidaan liikkua SUORAAN\n";
        continue;
      }
      if(getRuudunTyyppi(getUusiSijainti(VAS_)) == VAPAA) {
        std::cout << "voidaan liikkua VAS\n";
        continue;
      }
      

    }



  }


  /*
    Nykyistä sijaintia apuana käyttäen, palauttaa
    ensimmäisen mahdollisen SUUNNAN (charina) johon voidaan liikkua.
    Ensisijaiesti tarkastetaan oikea, suoraan ja vasemmalle.
  */
  sijainti_t Sokkelo::getUusiSijainti(const Yritys yritys) {

    
    const char TULOSUUNTA = this->suunta; // nykyinen menosuunta. Sama asia --> x -->
    const sijainti_t nyk = this->pino().top();

    sijainti_t uusi;
    uusi.first = nyk.first; uusi.second = nyk.second;

    // (1) Laske uusi sijanti menosuunnan (eli mistäpäin tultiin nyk. ruutuun)
    //  [ ][4][ ]
    //  [1][x][3]
    //  [ ][2][ ]
    // (2) Katso onko tämä uusi sijainti mahdollinen. Jos on, palauta sen suunnan char-enum

    if( (TULOSUUNTA == YLOS && yritys==OIK_) || (TULOSUUNTA==OIK && yritys==SUOR_) || (TULOSUUNTA==ALAS && yritys==VAS_))  {
      // rivi pysyy samana
      uusi.second--; // vaakarivi yhden vas.
    }
    else if( (TULOSUUNTA == VAS && yritys==OIK_) || (TULOSUUNTA==YLOS && yritys==SUOR_) || (TULOSUUNTA==OIK && yritys==VAS_) ) {
      uusi.first++; // rivi kasvaa
    }
    else if( (TULOSUUNTA == YLOS && yritys==VAS_) || (TULOSUUNTA==VAS && yritys==SUOR_) || (TULOSUUNTA==ALAS && yritys==OIK_) ) {
      uusi.second++; // vaakarivi yhden oik.
    }
    else {
      uusi.first--; // rivi ylös
    }

    // uusi kertoo siis mikä on oikea riippuen kulkusuunnasta.
    // Se ei välttämättä ole kuitenkaan laillinen ruutu!
    return uusi;

  }

  // Getteri stackille.
  stakki_t Sokkelo::pino() const {
    return this->stakki;
  }

  // Onko X reunalla?
  bool Sokkelo::onkoReunalla() {
    return false; // todo
  }


  char Sokkelo::getRuudunTyyppi( const sijainti_t& sijainti ) {

    try {
      
      // rivi, sarake
      return (char) this->sokkelo.at(sijainti.first).at(sijainti.second);

    } catch(...) {
      return '0';
    }

  }

  // On luokan Sokkelo ystävä
  /*
    Tulostaa sokkelon
    [#][ ][x]
    [#][#][ ]
  */
  std::ostream& operator << (std::ostream& out, const Sokkelo& s) {

    for(unsigned int ri=0; ri < s.sokkelo.size(); ++ri) {
      for(unsigned int ci=0; ci < s.sokkelo.at(ri).size(); ++ci) {
        //std::cout << ri << ", " << ci << "\n";
        out << s.sokkelo.at(ri).at(ci);
      }
      out << std::endl;
    }
    return out;

  }


  
}
