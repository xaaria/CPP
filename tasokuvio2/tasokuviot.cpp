#include <iostream>
#include <cmath>
#include "tasokuviot.h"
// tasokuviot.cpp
// >> g++ tasokuviot.cpp tasokuviot.h tasokuviotMain.cpp -o tasokuviot

// Oletusarvot on suotavaa esitellä vain kerran. Otsaketiedostossa(?!)

namespace otecpp_tasokuviot {

  Tasokuvio::~Tasokuvio() { }
  double Tasokuvio::pinta_ala() const {
    // tyhjä toteutus. Alaluokan tehtävä tehdä toteutus!
  }

  void Tasokuvio::tulosta(std::ostream &virta) const {
    // Tyhjä myös...
  }



  // end of abst. Tasokuvio

  Piste::Piste(double x, double y) : x(x), y(y) {
    std::cout << "Luodaan " << *this << "\n";
  }

  Piste::~Piste() {
    std::cout << "Tuhotaan " << *this << "\n";
  }



  // --- end of Piste ---


  Kolmio::Kolmio(const Piste& a, const Piste& b, const Piste& c)
    : a_(a), b_(b), c_(c) {
    std::cout << "Luodaan " << *this << "\n";
  }

  Kolmio::Kolmio(const Kolmio& kolmio)
    : a_(kolmio.a()), b_(kolmio.b()), c_(kolmio.c()) {

  }

  Kolmio::~Kolmio() {
    std::cout << "Tuhotaan " << *this << "\n";
  }

  // Getterit
  const Piste& Kolmio::a() const { return this->a_; }
  const Piste& Kolmio::b() const { return this->b_; }
  const Piste& Kolmio::c() const { return this->c_; }

  // Setterit
  double Kolmio::sivu1() const {
    return eukldist( this->a(), this->b() );
  }
  double Kolmio::sivu2() const {
     return eukldist( this->b(), this->c() );
  }
  double Kolmio::sivu3() const {
     return eukldist( this->a(), this->c() );
  }

  /* ((a.x - c.x)*(b.y - a.y) - (a.x - b.x)*(c.y - a.y))/2 itseisarvo. */
  double Kolmio::pinta_ala() const {
    return std::abs(
      (
        (this->a().x - this->c().x) * (this->b().y - this->a().y) -
        (this->a().x - this->b().x) * (this->c().y - this->a().y)
      )/2  
    );
  }

  void Kolmio::tulosta(std::ostream &virta) const {
    virta << "<" << this->a() << ", " << this->b() << ", " << this->c() << ">";
  }


  // end of Kolmio



  // Rakennin. Oletusarvo Piste() (eli (0,0) ja (0,0))
  Suorakulmio::Suorakulmio(const Piste &va, const Piste &oy) : va(va), oy(oy) {
    std::cout << "Luodaan " << *this << "\n";
  }

  Suorakulmio::Suorakulmio(const Suorakulmio& sk) : va(sk.vasenAlakulma()), oy(sk.oikeaYlakulma()) {
    std::cout << "Luodaan kopio " << *this << "\n"; 
  }

  Suorakulmio::~Suorakulmio() {
    std::cout << "Tuhotaan " << *this << "\n";
  }


  /* Getterit ja Setterit */

  const Piste& Suorakulmio::vasenAlakulma() const {
    return this->va;
  }


  const Piste& Suorakulmio::oikeaYlakulma() const {
    return this->oy;
  }

  // Setterit
  void Suorakulmio::vasenAlakulma(const Piste& va) {
    this->va = va;
  }
  void Suorakulmio::oikeaYlakulma(const Piste& oy) {
    this->oy = oy;
  }







  /* const, metodi on read-only, eli kerrotaan ettei muuteta tilaa */
  double Suorakulmio::leveys() const {
    return oy.x - va.x;
  }

  double Suorakulmio::korkeus() const {
    return oy.y - va.y;
  }

  double Suorakulmio::pinta_ala() const {
    return Suorakulmio::leveys() * Suorakulmio::korkeus();
  }

  void Suorakulmio::tulosta(std::ostream &virta) const {
    virta << "[" << this->vasenAlakulma() << ", " << this->oikeaYlakulma() << "]";
  }

  // ----

  std::ostream& operator<<(std::ostream& tuloste, const Piste& p) {
    tuloste << "(" << p.x << ", " << p.y << ")";  
    return tuloste;
  }


  std::ostream& operator<<(std::ostream &tuloste, const Tasokuvio &tk) {
    tk.tulosta(tuloste); // toiminta riippuu mitä tyyppiä tk on 
    return tuloste;
  }

  /*
  Eivät käytössä tässä versiossa

  std::ostream& operator<<(std::ostream& tuloste, const Suorakulmio& s) {
    tuloste << "[" << s.vasenAlakulma() << ", " << s.oikeaYlakulma() << "]";
    return tuloste;
  }


  std::ostream& operator<<(std::ostream& tuloste, const Kolmio& k) {
    tuloste << "<" << k.a() << ", " << k.b() << ", " << k.c() << ">";
    return tuloste;
  }
  */

  // Apustajat

  double eukldist(const Piste& a, const Piste& b) {
    return std::sqrt(
      std::pow(a.x - b.x, 2) + std::pow(a.y - b.y ,2)
    );
  }


}