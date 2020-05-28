#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <sstream>
#include <utility>
#include "sokkelo.h"

// sokkelo.cpp
const bool DE = true;
const bool OUTPUT = false;

namespace otecpp_sokkelo {

  /* Lukee sokkeloruudukon syötevirrasta in */
  Sokkelo::Sokkelo(std::istream& in) : lev(0), kork(0) {

    this->suunta = OIK;
    this->suuntahistoria.push(OIK);

    unsigned int r = 0; // rivi
    char line[100];

    while( in.getline(line, 60, '\n') ) {
      
      this->kork += 1;

      // lisää tyhjä char-rivi sokkelon rakenteeseen
      this->sokkelo.push_back( std::vector<char>() );
      //std::cout << line << "\n";
      std::stringstream ss(line);
      ss << std::noskipws; // älä skippaa valkomerkkejä (välil.)
      char c;

      while(ss >> c) {
        this->sokkelo.at(r).push_back( c ); 

        // Aseta pinoon alkuruudun rivi ja sarake. voidaan olettaa että vain yksi alkusij. ('X')
        if( c == SIJ) {
          //std::cout << "Aloitussijainti 'X' paikassa: " << r << "," << this->sokkelo.at(r).size()-1;
          this->liiku( std::make_pair(r, this->sokkelo.at(r).size()-1) ); // sen hetkisen koon mukaan!
          this->lev += 1;
        }

      }
      ++r; // kasvata riviä

    }

    // Debug/output-tiedosto
    this->output.open("sokkelo_out.txt");
    

  }

  /*
    Suorittaa liikkumisen [ohjeen kohdan 3] hakuaskeleen x kertaa (jos mahdollista).
    Ruudun tulee olla tyypiltään VAPAA.
    Eli palautetaan FALSE, jos joko löydettiin reitti ulos sokkelosta tai hakupino tuli tyhjäksi.
    (eli ts., jatketaanko liikkumista)
  */
  inline bool Sokkelo::askella(unsigned int x) {

    // Triviaali tarkastus A
    // TODO if(this->onkoReunalla()) { return false; }

    // Suorita X kertaa, tai poistu kesken pois jos ei mahd.
    for(unsigned int kerta=0; kerta<x; ++kerta ) {

      sijainti_t uusi;
      this->output << "~~[ askella() alkaa ]~~\n";
      // Yritä ensin oik.

      if(getRuudunTyyppi(uusi=getUusiSijainti(OIK_)) == VAPAA) {
        this->output << "\t--> voitiin liikkua OIK \n";
      }
      else if(getRuudunTyyppi(uusi=getUusiSijainti(SUOR_)) == VAPAA) {
        this->output << std::cout << "\t--> voitiin liikkua SUORAAN \n";
      }
      else if(getRuudunTyyppi(uusi=getUusiSijainti(VAS_)) == VAPAA) {
        this->output << "\t--> voitiin liikkua VAS\n";
      } else {
        // Ei mahdollisia liikkumissuuntia. Peruuta
        this->output << "\t--> ei voitu liikkua... Aloitetaan taaksepain liikkuminen...\n";

        // Joss pino tyhjenee, palauta false
        if (this->liikuTaaksepain() == EI_MIKAAN) {
          this->output << "\tEi mahdollisia suuntia! Lopeta suoritus...\n";
          return false;
        }

        // liikuttiin taaksepäin ilman että pino on tyhjä (= ei ulospääsyä)
        if(OUTPUT) this->output << "Liikkeen jälkeen: \n" << *this << "\n\n";
        continue;

      }

      // Lisää uusi sij. stakkiin, vain jos normaali liike
      
      this->liiku( uusi ); // normaali liike
      if(OUTPUT) this->output << "Liikkeen jälkeen: \n" << *this << "\n";
      

    }

    // Tarkista aivan lopuksi jatketaanko suoritusta.
    // Eli oliko ruutu johon päädyttiin, poispääsy
    // palauta käänteinen, eli jos ei, true, eli jatketaan
    this->output << "Katsotaan ollaanko reunalla...\n\n";
    return !this->onkoReunalla();

  }

  /*
    Lisää oikeellisen ruudun uudeksi sijainniksi, päivitää
    liike-pinon ja merkitsee sokkelo-vektoriin oikean merkin.
    Muuttaa kulkusuunnan perustuen pinon päällimmäiseen arvoon ja
    uuden sij. mukaan.
  */
  inline void Sokkelo::liiku(const sijainti_t& ruutu) {

    // Triviaali tarkastus
    // Aloitussijainnin lisäys ensimmäiseksi.
    // Suunta asetetaan rakentimessa
    if(this->pino().size() == 0) {
      this->stakki.push( ruutu );
      return;
    }

    // Päivitä tulosuunta
    this->output << "liiku() :\n";

    const sijainti_t sijainti_ennen = this->pino().top();

    this->output << "\tvanha (" << sijainti_ennen.first << "," << sijainti_ennen.second << ")\n";  
    this->output << "\tuusi  (" << ruutu.first << "," << ruutu.second << ")\n";  

    if( ruutu.first+1 == sijainti_ennen.first) {
      this->suunta = YLOS;
    }
    else if( ruutu.second-1 == sijainti_ennen.second ) {
      this->suunta = OIK;
    }
    else if( ruutu.first-1 == sijainti_ennen.first ) {
      this->suunta = ALAS;
    }
    else if(ruutu.second+1 == sijainti_ennen.second ) {
      this->suunta = VAS;
    }

    // Työnnä uusi suunta historiaan
    this->suuntahistoria.push(this->suunta);

    this->output << "suunta on nyt (0=ylos, 1=oik, ...): " << this->suunta << std::endl;
    
    

    // Päivitä sokkelon kuvio käydyksi. <rivi, sarake> = 'x'
    this->vaihdaRuutu(sijainti_ennen, X);   // vanha sijainti 
    this->vaihdaRuutu(ruutu, SIJ);          // uusi sijainti

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
  inline Suunta Sokkelo::liikuTaaksepain() {

    this->output << "liikuTaaksepain()\n";
    // Merkitse nyk. sijainti käydyksi ruudukkoon
    const sijainti_t NYK = this->pino().top();
    this->vaihdaRuutu(NYK, KAYTY); // <rivi, sarake> = '*'    

    //std::cout << *this;

  
    // Poista lopuksi päällimmäinen alkio. 
    // "Jos pino on tyhjä, ei nykyruutua enää ole ja haku päättyy tuloksettomana: sokkelosta ei löytynyt reittiä ulos."
    // -- Voidaan lopettaa metodi
    //std::cout << "pop. pinon koko on nyt: " << this->stakki.size();
    
    this->stakki.pop();
    // Poista päällimmäinen historiasta. Suunnan määritys tehdään siis 2. edellisen mukaan.
    //_this->suuntahistoria.pop();

    if(this->stakki.size() == 0) {
      this->output << "<Ei ulospaasya!>\n";
      return EI_MIKAAN; // ei jatketa
    }

    // OSA 2 -- Jos löytyy mahdollisuuksia, jatka normaalisti 
    // Peruutuksen yhteydessä nykyinen kulkusuunta muuttuu aiempaa etenemissuuntaa päinvastaiseksi.
    const Suunta ed_suunta = this->suuntahistoria.top(); // eli ns. 2. uusin
    try { 
      this->suuntahistoria.pop(); // siirretty top:n j�lkeiseksi
    } catch(...) { throw "Pinovirhe!"; }

    if     (ed_suunta == YLOS) {  this->suunta = ALAS;  }
    else if(ed_suunta == OIK) {   this->suunta = VAS;   }
    else if(ed_suunta == ALAS) {  this->suunta = YLOS;  }
    else if(ed_suunta == VAS) {   this->suunta = OIK;   }
    else { throw "Suuntavirhe!"; }
    
    // Poppaus tehty, sitten päivitä uusi päällimmäinen nykyiseksi ruuduksi, eli vanha x -> X:ksi
    this->vaihdaRuutu(this->stakki.top(), SIJ); // x x x X --> x x X *
    
    // Lopuksi tulostele tietoja & palauta "uusi" (=nyk.) kulkusuunta
    this->output << "\t suunta painvastaiseen: " << this->suunta << std::endl;
    this->output << "\t sijainti nyt: (" << this->stakki.top().first << "," << this->stakki.top().second << ")" << std::endl;
    
    return this->suunta;

  }


  /*
    Nykyistä sijaintia apuana käyttäen, palauttaa
    ensimmäisen mahdollisen SUUNNAN (charina) johon voidaan liikkua.
    
    Ensisijaiesti tarkastetaan: oikea, suoraan ja vasemmalle.
    Param. yritys kertoo mihin suuntaan yritetään
  */
  inline sijainti_t Sokkelo::getUusiSijainti(const Yritys yritys) {

    
    const short SUUNTA     = this->suunta; // nykyinen MENO_suunta
    const sijainti_t nyk   = this->pino().top();

    sijainti_t uusi;
    uusi.first = nyk.first; uusi.second = nyk.second; // alustetaan nyk. sijaintiin

    this->output << "---\nSuunta: [0=ylos, 1=oik.,] " << this->suunta << " | Yritetaan: [0=oikealle, 1=suoraan, 2=vas.] " << yritys << " @ (" << nyk.first << "," << nyk.second  << ")\n";

    // (1) Laske uusi sijanti suunnan mukaan (eli MIHIN SUUNTAAN OLLAAN MENOSSA)
    // Esim case 1 tarkoittaa että päädytään tähän ruutuun. If-lause kertoo vast. kombinaatiot
    //  [ ][4][ ]
    //  [1][x][3]
    //  [ ][2][ ]
    // (2) Katso onko tämä uusi sijainti mahdollinen.

    if( (SUUNTA == YLOS && yritys==VAS_) || (SUUNTA==VAS && yritys==SUOR_) || (SUUNTA==ALAS && yritys==OIK_))  {
      // rivi pysyy samana
      //std::cout << "case 1\n";
      uusi.second--; // vaakarivi yhden vas.
    }
    else if( (SUUNTA == VAS && yritys==VAS_) || (SUUNTA==ALAS && yritys==SUOR_) || (SUUNTA==OIK && yritys==OIK_) ) {
      //std::cout << "case 2\n";
      uusi.first++; // rivi kasvaa
    }
    else if( (SUUNTA == OIK && yritys==SUOR_) || (SUUNTA == YLOS && yritys==OIK_) || (SUUNTA==ALAS && yritys==VAS_) ) {
      //std::cout << "case 3\n";
      uusi.second++; // vaakarivi yhden oik.
    }
    else if( (SUUNTA == YLOS && yritys==SUOR_) || (SUUNTA == OIK && yritys==VAS_) || (SUUNTA==VAS && yritys==OIK_) ) {
      //std::cout << "case 4, other\n";
      uusi.first--; // rivi ylös
    } else {
      throw "Ei voitu määrittää uutta ruutua!";
    }

    // uusi kertoo siis mikä on oikea riippuen kulkusuunnasta.
    // Se ei välttämättä ole kuitenkaan laillinen ruutu!
    // Palauta sijainti pair: rivi, sarake
    this->output << "Uusi ruutu voisi olla: (" << uusi.first << "," << uusi.second << ") [Liikutaan jos ruutu on vapaa!]" << std::endl;
    return uusi;

  }

  bool Sokkelo::vaihdaRuutu(const sijainti_t& sijainti, const char uusi) {

    // Hae pointteri ruutuun
    this->output << "Vaihdetaan ruudun (" << sijainti.first << "," << sijainti.second << ") merkki | ";
    char* vanha = &( this->sokkelo.at(sijainti.first).at(sijainti.second) );
    *vanha = uusi; 
    this->output << *vanha << " -> " << uusi << "\n";
    return true;
  }

  // Getteri stackille. Huomaa kopio (!)
  stakki_t Sokkelo::pino() const {
    return this->stakki;
  }

  // Onko X reunalla?
  // Huomaa, että rivien ja sarakkeiden arvo on niiden lukumäärä
  bool Sokkelo::onkoReunalla() {
    const sijainti_t NYK = this->pino().top(); // nykyinen sijaintimme
    return (NYK.first+1 == 1 || NYK.second+1 == 1 || NYK.first+1 == this->kork || NYK.second+1 == this->lev);
  }


  char Sokkelo::getRuudunTyyppi( const sijainti_t& sijainti ) {

    // rivi, sarake
    return (char) this->sokkelo.at(sijainti.first).at(sijainti.second);
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
