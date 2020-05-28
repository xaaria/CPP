#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <utility> /* pair */

// sokkelo.h

namespace otecpp_sokkelo {


  const char SEINA = '#';
  const char VAPAA = ' ';
  const char SIJ   = 'X'; // Nykyist� sijaintia merkkaava merkki
  const char X     = 'x'; // ruutu jossa on k�yty (my�s jossa ollaan parasta aikaa). HUOM! tiedostoa lukiessa merkki on iso 'X'
  const char KAYTY = '*'; // ruudut, joissa on jo k�yty, mutta jotka eiv�t ole nykyruudun ja l�ht�ruudun v�lisell� polulla

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

      // Lis�� liikkeen pinoon ja p�ivitt�� this.sokkelon jotta piirto onnistuu, sek� muuttaa kulkusuunnan
      // Liikkeen oletetaan olevan oikeellinen(!)
      // -- Eli ei sein�� ja k�ym�t�n
      void liiku(const sijainti_t& uusi_sijainti);

      // Peruu viimeisimm�n liikkeen, eli liikepinon p��llimm�isen, ja muuttaa kulkusuunnan
      Suunta liikuTaaksepain();
      

      bool onkoReunalla();

      // Yst�v�m��ritys:
      // eli ett� ulkopuolisella vast. funk. on p��sy param. yksityisiin j�seniin
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

      // K�y l�pi nykyisen sij. suhteen 1. vapaan SUUNNAN (tarkistaa ensin oikean, jne...)
      char getMahdollinenSuunta();

      // Palauttavat sijainti-parin nyk. haluttuun suuntaan nyk. sijainnista
      // Saa parametriksi sen suunnan mihin ollaan yritt�m�ss�
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