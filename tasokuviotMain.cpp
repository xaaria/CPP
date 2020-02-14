#include <iostream>
#include "tasokuviot.h"
#include <vector>

using namespace std;
using otecpp_tasokuviot::Piste;
using otecpp_tasokuviot::Suorakulmio;

int main(int argc, char *argv[])
{
  Suorakulmio sk(Piste(-1.5, -2.5), Piste(2.5, 1.5));
  vector<Suorakulmio> skt(2); // Luo 2 oletusalustettua suorakulmiota.
  skt.push_back(sk);          // Lisätään perään vielä sk.
  skt[0].vasenAlakulma(Piste(1, 1));  // Olion skt[0] vasen alakulma --> (1, 1).
  skt[0].oikeaYlakulma(Piste(2, 2));  // Olion skt[0] oikea yläkulma --> (2, 2).
  const vector<Suorakulmio> &sktVakioviite = skt; // Vakioviite vektoriin skt.
  for(vector<Suorakulmio>::size_type i = 0; i < sktVakioviite.size(); ++i)
  {
    const Piste &va = skt[i].vasenAlakulma();  // Viite vasempaan alakulmaan.
    const Piste &oy = skt[i].oikeaYlakulma();  // Viite oikeaan yläkulmaan.
    cout << "((" << va.x << ", " << va.y << "), ("
                  << oy.x << ", " << oy.y << "))\n"; 
  }
}