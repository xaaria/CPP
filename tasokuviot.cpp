#include <iostream>
#include "tasokuviot.h"
// tasokuviot.cpp

// Oletusarvot on suotavaa esitellä vain kerran. Otsaketiedostossa(?!)

namespace otecpp_tasokuviot {


  Piste::Piste(double x, double y) : x(x), y(y) {
    std::cout << "Luodaan Piste(" << x << ", " << y << ")\n";
  }

  Piste::~Piste() {
    std::cout << "Tuhotaan Piste(" << x << ", " << y << ")\n";
  }


  // Rakennin. Oletusarvo Piste() (eli (0,0) ja (0,0))
  Suorakulmio::Suorakulmio(const Piste &va, const Piste &oy) : va(va), oy(oy) {
    std::cout << "Luodaan Suorakulmio((" << va.x << ", " << va.y << "), ("
    << oy.x << ", " << oy.y << "))\n";
  }

  Suorakulmio::Suorakulmio(const Suorakulmio& sk) : va(sk.va), oy(sk.oy) {
    std::cout << "Luodaan kopio Suorakulmio((" << 
      va.x << ", " << va.y << "), (" << oy.x << ", " << oy.y << "))\n"; 
  }

  Suorakulmio::~Suorakulmio() {
    std::cout << "Tuhotaan Suorakulmio((" << va.x << ", " << va.y << "), ("
    << oy.x << ", " << oy.y << "))\n";
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


}