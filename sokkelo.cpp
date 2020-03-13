#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <utility>
#include "sokkelo.h"

// sokkelo.cpp

namespace otecpp_sokkelo {

  /* Lukee sokkeloruudukon sy�tevirrasta in */
  Sokkelo::Sokkelo(std::istream& in) {

    this->suunta = OIK;

    unsigned int r = 0; // rivi
    char line[100];

    while( in.getline(line, 100, '\n') ) {
      
      // lis�� tyhj� char-rivi sokkelon rakenteeseen
      this->sokkelo.push_back( std::vector<char>() );
      //std::cout << line << "\n";
      std::stringstream ss(line);
      ss << std::noskipws; // �l� skippaa valkomerkkej� (v�lil.)
      char c;

      while(ss >> c) {
        this->sokkelo.at(r).push_back( tolower(c) ); 

        // Aseta pinoon alkuruudun rivi ja sarake. voidaan olettaa ett� vain yksi alkusij. ('X')
        if( c == 'X') {
          //std::cout << "Aloitussijainti x paikassa: " << r << "," << this->sokkelo.at(r).size()-1;
          this->liiku( std::make_pair(r, this->sokkelo.at(r).size()-1) );
        }

      }
      ++r; // kasvata rivi�

    }

  }

  /*
    Suorittaa liikkumisen [ohjeen kohdan 3] hakuaskeleen x kertaa (jos mahdollista).
    Ruudun tulee olla tyypilt��n VAPAA.
    Eli palautetaan FALSE, jos joko l�ydettiin reitti ulos sokkelosta tai hakupino tuli tyhj�ksi.
    (eli ts., jatketaanko liikkumista)
  */
  bool Sokkelo::askella(unsigned int x) {

    // Triviaali tarkastus A
    // TODO if(this->onkoReunalla()) { return false; }

    // Suorita X kertaa, tai poistu kesken pois jos ei mahd.
    for(unsigned int kerta=0; kerta<x; ++kerta ) {

      sijainti_t uusi;
      std::cout << "### ###\n\n";
      // Yrit� ensin oik.
      //Yritys y = OIK_;
      if(getRuudunTyyppi(uusi=getUusiSijainti(OIK_)) == VAPAA) {
        std::cout << "\t--> voitiin liikkua OIK \n";
      }
      else if(getRuudunTyyppi(uusi=getUusiSijainti(SUOR_)) == VAPAA) {
        std::cout << "\t--> voitiin liikkua SUORAAN \n";
      }
      else if(getRuudunTyyppi(uusi=getUusiSijainti(VAS_)) == VAPAA) {
        std::cout << "\t--> voitiin liikkua VAS\n";
      } else {
        // Ei mahdollisia liikkumissuuntia. Peruuta
        std::cout << "\t--> ei voitu liikkua...\n";

        this->liikuTaaksepain();
        return (this->pino().size() > 0); // Palauta true kun jatketaan

      }

      // Lis�� uusi sij. stakkiin
      this->liiku( uusi ); // normaali liike
      

    }


    return true;
  }

  /*
    Lis�� oikeellisen ruudun uudeksi sijainniksi, p�ivit��
    liike-pinon ja merkitsee sokkelo-vektoriin oikean merkin.
    Muuttaa kulkusuunnan perustuen pinon p��llimm�iseen arvoon ja
    uuden sij. mukaan.
  */
  void Sokkelo::liiku(const sijainti_t& ruutu) {

    // Triviaali tarkastus
    // Aloitussijainnin lis�ys ensimm�iseksi.
    // Suunta asetetaan rakentimessa
    if(this->pino().size() == 0) {
      this->stakki.push( ruutu );
      return;
    }

    // P�ivit� tulosuunta
    std::cout << "liiku() :\n";

    const sijainti_t sijainti_ennen = this->pino().top();

    std::cout << "vanha (" << sijainti_ennen.first << "," << sijainti_ennen.second << ")\n";  
    std::cout << "uusi  (" << ruutu.first << "," << ruutu.second << ")\n";  

    if( ruutu.first+1 == sijainti_ennen.first) {
      this->suunta = YLOS;
    }
    if( ruutu.second-1 == sijainti_ennen.second ) {
      this->suunta = OIK;
    }
    if( ruutu.first-1 == sijainti_ennen.first ) {
      this->suunta = ALAS;
    }
    if(ruutu.second+1 == sijainti_ennen.second ) {
      this->suunta = VAS;
    }
    std::cout << "suunta on nyt " << this->suunta << std::endl;
    
    

    // P�ivit� sokkelon kuvio k�ydyksi. <rivi, sarake> = 'x'
    this->sokkelo.at(ruutu.first).at(ruutu.second) = X;

    // Lis�� liike pinoon
    this->stakki.push( ruutu );

  }

  /*
    Jos liike-vaiheessa ei l�ytynyt vapaata ja toistaiseksi k�ym�t�nt� ruutua, peruutetaan askel taaksep�in: 
      merkit��n nykyruutu k�ydyksi ja poistetaan pinon p��llimm�inen alkio.

    Jos pino on tyhj�, ei nykyruutua en�� ole ja haku p��ttyy tuloksettomana: sokkelosta ei l�ytynyt reitti� ulos.
    Peruutuksen yhteydess� nykyinen kulkusuunta muuttuu aiempaa etenemissuuntaa p�invastaiseksi.

    return: uusi (kulku)Suunta enum.
  */
  Suunta Sokkelo::liikuTaaksepain() {

    std::cout << "liikuTaaksepain()\n";

    // Ei suoriteta jos pino on jo tyhj�
    if(this->pino().size() == 0) { return MUU; }

    // Merkitse nyk. sijainti k�ydyksi ruudukkoon
    const sijainti_t NYK = this->pino().top();
    this->sokkelo.at(NYK.first).at(NYK.second) = KAYTY; // <rivi, sarake> = '*'    

    // Vaihda kulkusuunta
    if(this->suunta == 0) { this->suunta = ALAS; }
    else if(this->suunta == 1) { this->suunta = VAS; }
    else if(this->suunta == 2) { this->suunta = YLOS; }
    else if(this->suunta == 3) { this->suunta = OIK; }
    else if(this->pino().size() == 1) { this->suunta = MUU; } // poiston j�lkeen pino on tyhj�, eli alku. Silloin suunta on MUU

    // Poista lopuksi p��llimm�inen alkio. 
    // Pino saattaa tyhjenty�. T�ll�in suunta on MUU
    this->stakki.pop();

    // Lopuksi palauta uusi/nyk. kulksuunta
    std::cout << "\t suunta painvastaiseen: " << this->suunta << std::endl;
    return this->suunta;

  }


  /*
    Nykyist� sijaintia apuana k�ytt�en, palauttaa
    ensimm�isen mahdollisen SUUNNAN (charina) johon voidaan liikkua.
    
    Ensisijaiesti tarkastetaan: oikea, suoraan ja vasemmalle.
    Param. yritys kertoo mihin suuntaan yritet��n
  */
  sijainti_t Sokkelo::getUusiSijainti(const Yritys yritys) {

    
    const short SUUNTA     = this->suunta; // nykyinen MENO_suunta
    const sijainti_t nyk  = this->pino().top();

    sijainti_t uusi;
    uusi.first = nyk.first; uusi.second = nyk.second; // alustetaan nyk. sijaintiin

    std::cout << "---\nSuunta: " << this->suunta << " | Yritetaan: " << yritys << " @ (" << nyk.first << "," << nyk.second  << ")\n";

    // (1) Laske uusi sijanti suunnan mukaan (eli MIHIN SUUNTAAN OLLAAN MENOSSA)
    // Esim case 1 tarkoittaa ett� p��dyt��n t�h�n ruutuun. If-lause kertoo vast. kombinaatiot
    //  [ ][4][ ]
    //  [1][x][3]
    //  [ ][2][ ]
    // (2) Katso onko t�m� uusi sijainti mahdollinen.

    if( (SUUNTA == YLOS && yritys==VAS_) || (SUUNTA==VAS && yritys==SUOR_) || (SUUNTA==ALAS && yritys==OIK_))  {
      // rivi pysyy samana
      std::cout << "case 1\n";
      uusi.second--; // vaakarivi yhden vas.
    }
    else if( (SUUNTA == VAS && yritys==VAS_) || (SUUNTA==ALAS && yritys==SUOR_) || (SUUNTA==OIK && yritys==OIK_) ) {
      std::cout << "case 2\n";
      uusi.first++; // rivi kasvaa
    }
    else if( (SUUNTA == OIK && yritys==SUOR_) || (SUUNTA == YLOS && yritys==OIK_) || (SUUNTA==ALAS && yritys==VAS_) ) {
      std::cout << "case 3\n";
      uusi.second++; // vaakarivi yhden oik.
    }
    else {
      std::cout << "case 4, other\n";
      uusi.first--; // rivi yl�s
    }

    // uusi kertoo siis mik� on oikea riippuen kulkusuunnasta.
    // Se ei v�ltt�m�tt� ole kuitenkaan laillinen ruutu!
    // Palauta sijainti pair: rivi, sarake
    std::cout << "Uusi ruutu [voisi olla]: (" << uusi.first << "," << uusi.second << ")" << std::endl;
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

  // On luokan Sokkelo yst�v�
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
