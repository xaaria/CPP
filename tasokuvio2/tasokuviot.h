#include <iostream>

/*
  Tasokuviot #2
*/

namespace otecpp_tasokuviot {

  // Abstrakti luokka Tasokuvio

  class Tasokuvio {

    public:
      virtual ~Tasokuvio();
      virtual double pinta_ala() const;

    private:
      virtual void tulosta(std::ostream &virta) const;
      friend std::ostream& operator<<(std::ostream& tuloste, const Tasokuvio& tk);

  };






  class Piste {

    public:
      double x;
      double y;

      Piste(double x=0, double y=0);
      ~Piste();


    };


    class Suorakulmio : public Tasokuvio {

      // vasen alakulma ja oikea yläkulma
      Piste va;
      Piste oy;

      public:
        // Rakennin. Oletusarvo Piste()-viitteet (oletus (0,0) ja (0,0))
        Suorakulmio(const Piste& va=Piste(), const Piste& oy=Piste());
        // Kopiorakennin
        Suorakulmio(const Suorakulmio& sk);
        ~Suorakulmio();

        // Getterit
        const Piste& vasenAlakulma() const;
        const Piste& oikeaYlakulma() const;

        // Setterit
        void vasenAlakulma(const Piste& va);
        void oikeaYlakulma(const Piste& oy);

        /* const, metodi on read-only, eli kerrotaan ettei muuteta olion tilaa */
        double leveys() const;
        double korkeus() const;
        double pinta_ala() const;

        // Tulostus
        void tulosta(std::ostream &virta) const;

    };


  double eukldist(const Piste& a, const Piste& b);

  class Kolmio : public Tasokuvio {

    private:
      Piste a_;
      Piste b_;
      Piste c_; /* kulmat */

    public:
    
      Kolmio(const Piste &a=Piste(), const Piste &b=Piste(), const Piste &c=Piste());
      Kolmio(const Kolmio& kolmio);
      ~Kolmio();

      // Getterit
      const Piste& a() const;
      const Piste& b() const;
      const Piste& c() const;

      // Setterit
      double sivu1() const;
      double sivu2() const;
      double sivu3() const;

      double pinta_ala() const;

      // Tulostus
      void tulosta(std::ostream &virta) const;
  };


  // Tulostusoperaatiot. EI osaksi luokkia!
  std::ostream& operator<<(std::ostream &tuloste, const Piste &p); // virta << p
  
  // Polymorfinen kuormitus <<, joka kutsuu tk:n tulosta()... riippuen olion (ali)luokasta
  //std::ostream& operator<<(std::ostream &tuloste, const Tasokuvio &tk);

  /*std::ostream& operator<<(std::ostream &tuloste, const Suorakulmio &s);
  std::ostream& operator<<(std::ostream &tuloste, const Kolmio &k);
  */

  

}