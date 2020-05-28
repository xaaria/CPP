#include <fstream>
#include <iostream>
#include <utility>
#include "sanat.h"

using namespace std;
using namespace otecpp_sanat;

namespace
{  // typedef-aliaksia alla käytetyille iteraattorille
  typedef multimap<string, unsigned int>::iterator MultiIt;
  typedef map<string, unsigned int>::iterator MapIt;
  typedef map<string, vector<unsigned int> >::iterator VectorMapIt;
}

int main()
{
  ifstream syote("input.txt");  // Luetaan syötettä tiedostosta "input.txt"
  multimap<string, unsigned int> rivimm = rivit(syote);
  syote.close();
  pair<MultiIt, MultiIt> tulos = rivimm.equal_range("a");
  // Iteroidaan sanaa "a" koskevat rivitiedot läpi
  for(MultiIt it = tulos.first; it != tulos.second; ++it)
  { // Tulostetaan kukin tieto muodossa (sana, riviNro)
    cout << " (" << it->first << ", " << it->second << ")";
  }
  cout << "-----\n";
  set<string> hakusanat;
  hakusanat.insert("a");
  hakusanat.insert("b");
  syote.open("input.txt");  // Avataan syötetiedosto uudelleen
  multimap<string, unsigned int> tasmmm = tasmaavatRivit(syote, hakusanat);
  syote.close();
  // Iteroidaan sanajoukkoa "a" ja "b" koskevat rivitiedot läpi
  for(MultiIt it = tasmmm.begin(); it != tasmmm.end(); ++it)
  { // Tulostetaan kukin tieto muodossa (sana, riviNro)
    cout << " (" << it->first << ", " << it->second << ")";
  }
  cout << "-----\n";
  syote.open("input.txt");  // Avataan syötetiedosto uudelleen
  map<string, unsigned int> lkmt = sanaLkmt(syote);
  syote.close();
  // Iteroidaan sanojen lukumääriä koskevat tiedot läpi
  for(MapIt it = lkmt.begin(); it != lkmt.end(); ++it)
  { // Tulostetaan kukin tieto muodossa [sana: x kpl]
    cout << " [" << it->first << ": " << it->second << " kpl]";
  }
  cout << "-----\n";
  map<string, vector<unsigned int> > riviMap = rivitTaulukkoon(rivimm);
  syote.close();
  // Iteroidaan sanojen rivinumerotiedot läpi
  for(VectorMapIt it = riviMap.begin(); it != riviMap.end(); ++it)
  { // Tulostetaan kunkin sanan rivinumerot muodossa (sana, [rivinumerot])
    cout << " (" << it->first << ", [";
    for(vector<unsigned int>::size_type i = 0; i < it->second.size(); ++i)
    {
      if(i > 0)
      {
        cout << ", ";
      }
      cout << it->second[i];
    }
    cout << "])";
  }
  cout << "-----\n";
}