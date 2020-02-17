#include <iostream>
#include "tasokuviot.h"

using namespace std;
using otecpp_tasokuviot::Piste;
using otecpp_tasokuviot::Tasokuvio;
using otecpp_tasokuviot::Suorakulmio;
using otecpp_tasokuviot::Kolmio;

int main(int argc, char *argv[])
{ // Alla k‰sitell‰‰n suorakulmiota ja kolmiota Tasokuvio-osoittimen kautta.
  Tasokuvio *s = new Suorakulmio(Piste(-1.5, -2.5), Piste(2.5, 1.5));
  Tasokuvio *k = new Kolmio(Piste(0, 0), Piste(0, 2), Piste(2, 2));
  cout << "Tasokuviot " << *s << " ja " << *k << '\n';
  cout << "Pinta-alat: " << s->pinta_ala() << " ja " << k->pinta_ala() << '\n';
  delete s;
  delete k;
}