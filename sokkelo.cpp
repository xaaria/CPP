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
        this->sokkelo.at(r).push_back( tolower(c) ); 

        // Aseta pinoon alkuruudun rivi ja sarake. voidaan olettaa että vain yksi alkusij. ('X')
        if( c == 'X') {
          //std::cout << "Aloitussijainti x paikassa: " << r << "," << this->sokkelo.at(r).size()-1;
          this->liiku( std::make_pair(r, this->sokkelo.at(r).size()-1) );
        }

      }
      ++r; // kasvata riviä

    }

  }

  /*
    Suorittaa liikkumisen [ohjeen kohdan 3] hakuaskeleen x kertaa (jos mahdollista).
    Ruudun tulee olla tyypiltään VAPAA.
    Eli palautetaan FALSE, jos joko löydettiin reitti ulos sokkelosta tai hakupino tuli tyhjäksi.
    (eli ts., jatketaanko liikkumista)
  */
  bool Sokkelo::askella(unsigned int x) {

    // Triviaali tarkastus A
    // TODO if(this->onkoReunalla()) { return false; }

    // Suorita X kertaa, tai poistu kesken pois jos ei mahd.
    for(unsigned int kerta=0; kerta<x; ++kerta ) {

      sijainti_t uusi;
      std::cout << "### ###\n\n";
      // Yritä ensin oik.
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

      // Lisää uusi sij. stakkiin
      this->liiku( uusi ); // normaali liike
      

    }


    return true;
  }

  /*
    Lisää oikeellisen ruudun uudeksi sijainniksi, päivitää
    liike-pinon ja merkitsee sokkelo-vektoriin oikean merkin.
    Muuttaa kulkusuunnan perustuen pinon päällimmäiseen arvoon ja
    uuden sij. mukaan.
  */
  void Sokkelo::liiku(const sijainti_t& ruutu) {

    // Triviaali tarkastus
    // Aloitussijainnin lisäys ensimmäiseksi.
    // Suunta asetetaan rakentimessa
    if(this->pino().size() == 0) {
      this->stakki.push( ruutu );
      return;
    }

    // Päivitä tulosuunta
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
    
    

    // Päivitä sokkelon kuvio käydyksi. <rivi, sarake> = 'x'
    this->sokkelo.at(ruutu.first).at(ruutu.second) = X;

    // Lisää liike pinoon
    this->stakki.push( ruutu );

  }

  /*
    Jos liike-vaiheessa ei löytynyt vapaata ja toistaiseksi käymätöntä ruutua, peruutetaan askel taaksepäin: 
      merkitään nykyruutu käydyksi ja poistetaan pinon päällimmäinen alkio.

    Jos pino on tyhjä, ei nykyruutua enää ole ja haku päättyy tuloksettomana: sokkelosta ei löytynyt reittiä ulos.
    Peruutuksen yhteydessä nykyinen kulkusuunta muuttuu aiempaa etenemissuuntaa päinvastaiseksi.

    return: uusi (kulku)Suunta enum.
  */
  Suunta Sokkelo::liikuTaaksepain() {

    std::cout << "liikuTaaksepain()\n";

    // Ei suoriteta jos pino on jo tyhjä
    if(this->pino().size() == 0) { return MUU; }

    // Merkitse nyk. sijainti käydyksi ruudukkoon
    const sijainti_t NYK = this->pino().top();
    this->sokkelo.at(NYK.first).at(NYK.second) = KAYTY; // <rivi, sarake> = '*'    

    // Vaihda kulkusuunta
    if(this->suunta == 0) { this->suunta = ALAS; }
    else if(this->suunta == 1) { this->suunta = VAS; }
    else if(this->suunta == 2) { this->suunta = YLOS; }
    else if(this->suunta == 3) { this->suunta = OIK; }
    else if(this->pino().size() == 1) { this->suunta = MUU; } // poiston jälkeen pino on tyhjä, eli alku. Silloin suunta on MUU

    // Poista lopuksi päällimmäinen alkio. 
    // Pino saattaa tyhjentyä. Tällöin suunta on MUU
    this->stakki.pop();

    // Lopuksi palauta uusi/nyk. kulksuunta
    std::cout << "\t suunta painvastaiseen: " << this->suunta << std::endl;
    return this->suunta;

  }


  /*
    Nykyistä sijaintia apuana käyttäen, palauttaa
    ensimmäisen mahdollisen SUUNNAN (charina) johon voidaan liikkua.
    
    Ensisijaiesti tarkastetaan: oikea, suoraan ja vasemmalle.
    Param. yritys kertoo mihin suuntaan yritetään
  */
  sijainti_t Sokkelo::getUusiSijainti(const Yritys yritys) {

    
    const short SUUNTA     = this->suunta; // nykyinen MENO_suunta
    const sijainti_t nyk  = this->pino().top();

    sijainti_t uusi;
    uusi.first = nyk.first; uusi.second = nyk.second; // alustetaan nyk. sijaintiin

    std::cout << "---\nSuunta: " << this->suunta << " | Yritetaan: " << yritys << " @ (" << nyk.first << "," << nyk.second  << ")\n";

    // (1) Laske uusi sijanti suunnan mukaan (eli MIHIN SUUNTAAN OLLAAN MENOSSA)
    // Esim case 1 tarkoittaa että päädytään tähän ruutuun. If-lause kertoo vast. kombinaatiot
    //  [ ][4][ ]
    //  [1][x][3]
    //  [ ][2][ ]
    // (2) Katso onko tämä uusi sijainti mahdollinen.

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
      uusi.first--; // rivi ylös
    }

    // uusi kertoo siis mikä on oikea riippuen kulkusuunnasta.
    // Se ei välttämättä ole kuitenkaan laillinen ruutu!
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
