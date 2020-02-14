#include <iostream>
#include "tasokuviot.h"

using namespace std;
using otecpp_tasokuviot::Piste;
using otecpp_tasokuviot::Suorakulmio;
using otecpp_tasokuviot::Kolmio;

int main(int argc, char *argv[])
{
  Piste pt[5] = {Piste(-1.5, -2.5), Piste(2.5, 1.5),
                  Piste(0, 0), Piste(0, 2), Piste(2, 2)};
  cout << "5 pistettä: " << pt[0] << pt[1] << pt[2] << pt[3] << pt[4] << '\n';
  Suorakulmio s(pt[0], pt[1]);
  cout << "Suorakulmion " << s << " pinta-ala: " << s.pinta_ala() << '\n'; 
  Kolmio k(pt[2], pt[3], pt[4]);
  cout << "Kolmion " << k  << " sivujen pituudet: " << k.sivu1() << ", "
                              << k.sivu2() << " ja " << k.sivu3() << '\n';
  cout << "Kolmion " << k << " pinta-ala: " << k.pinta_ala() << '\n';  
}