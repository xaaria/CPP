#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <utility> /* pair */

// sokkelo.h

namespace otecpp_sokkelo {


  const char SEINA = '#';
  const char VAPAA = ' ';
  const char SIJ   = 'X'; // Nykyistä sijaintia merkkaava merkki
  const char X     = 'x'; // ruutu jossa on käyty (myös jossa ollaan parasta aikaa). HUOM! tiedostoa lukiessa merkki on iso 'X'
  const char KAYTY = '*'; // ruudut, joissa on jo käyty, mutta jotka eivät ole nykyruudun ja lähtöruudun välisellä polulla

  // Pino, jossa koordinaattipareja. Muotoa <RIVI, SARAKE>. Alkaa 0:sta
  typedef std::pair<unsigned int, unsigned int>     sijainti_t;
  typedef std::stack<sijainti_t>                    stakki_t; 
  typedef std::vector< std::vector<char> >          sokkelo_t; 
  enum Suunta { YLOS, OIK, ALAS, VAS, EI_MIKAAN }; // Kulkusuunta. 0,1,2,3
  enum Yritys { OIK_, SUOR_, VAS_ };

  class Sokkelo {
 
    public:
      Sokkelo(std::istream& in);

      // Getteri stackille.
      stakki_t pino() const;

      bool askella(unsigned int x);

      // Lisää liikkeen pinoon ja päivittää this.sokkelon jotta piirto onnistuu, sekä muuttaa kulkusuunnan
      // Liikkeen oletetaan olevan oikeellinen(!)
      // -- Eli ei seinää ja käymätön
      void liiku(const sijainti_t& uusi_sijainti);

      // Peruu viimeisimmän liikkeen, eli liikepinon päällimmäisen, ja muuttaa kulkusuunnan
      Suunta liikuTaaksepain();
      

      bool onkoReunalla();

      // Ystävämääritys:
      // eli että ulkopuolisella vast. funk. on pääsy param. yksityisiin jäseniin
      friend std::ostream& operator << (std::ostream& out, const Sokkelo& s);

    private:

      // Dimensiot. Alusta nollaksi
      unsigned short lev;
      unsigned short kork;

      std::ofstream output;

      stakki_t  stakki;
      sokkelo_t sokkelo;

      Suunta suunta;
      std::stack<Suunta> suuntahistoria; // pino, jossa tallessa suuntahistoria

      // Käy läpi nykyisen sij. suhteen 1. vapaan SUUNNAN (tarkistaa ensin oikean, jne...)
      char getMahdollinenSuunta();

      // Palauttavat sijainti-parin nyk. haluttuun suuntaan nyk. sijainnista
      // Saa parametriksi sen suunnan mihin ollaan yrittämässä
      // Saatu sijainti_t EI OLE automaattisesti kelpaava, vaan laskennallinen ehdotus
      sijainti_t getUusiSijainti(const Yritys yritys);

      // Palauttaa paikan <rivi, sarake> merkin charina
      char getRuudunTyyppi( const sijainti_t& sijainti );

      // Vaihtaa sijainnin merkin. Boolean sijoituksen laillisuudesta.
      bool vaihdaRuutu(const sijainti_t& sijainti, const char uusi);

  };


  // friend
  std::ostream& operator << (std::ostream& out, const Sokkelo& s);

}