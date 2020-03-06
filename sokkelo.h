#include <iostream>
#include <stack>
#include <vector>
#include <utility> /* pair */

// sokkelo.h

namespace otecpp_sokkelo {


  const char SEINA = '#';
  const char VAPAA = ' ';
  const char X     = 'x'; // ruutu jossa on käyty (myös jossa ollaan parasta aikaa)

  // Pino, jossa koordinaattipareja. Muotoa <RIVI, SARAKE>. Alkaa 0:sta
  typedef std::pair<unsigned int, unsigned int>     sijainti_t;
  typedef std::stack<sijainti_t>                    stakki_t; 
  typedef std::vector< std::vector<char> >          sokkelo_t; 
  enum Suunta { YLOS, OIK, ALAS, VAS, MUU }; // 0,1,2,3
  enum Yritys { OIK_, SUOR_, VAS_ };

  class Sokkelo {
 
    public:
      Sokkelo(std::istream& in);

      bool askella(unsigned int x);

      // Getteri stackille.
      stakki_t pino() const;

      bool onkoReunalla();

      // Ystävämääritys:
      // eli että ulkopuolisella vast. funk. on pääsy param. yksityisiin jäseniin
      friend std::ostream& operator << (std::ostream& out, const Sokkelo& s);

    private:
      stakki_t  stakki;
      sokkelo_t sokkelo;

      Suunta suunta;

      // Käy läpi nykyisen sij. suhteen 1. vapaan SUUNNAN (tarkistaa ensin oikean, jne...)
      char getMahdollinenSuunta();

      // Palauttavat sijainti-parin nyk. haluttuun suuntaan nyk. sijainnista
      // Saa parametriksi sen suunnan mihin ollaan yrittämässä
      sijainti_t getUusiSijainti(const Yritys yritys);
      //sijainti_t getSuora();
      //sijainti_t getVasen();

      // Palauttaa paikan <rivi, sarake> merkin charina
      char getRuudunTyyppi( const sijainti_t& sijainti );

  };


  // friend
  std::ostream& operator << (std::ostream& out, const Sokkelo& s);

}