#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "valuutat.h"

using namespace std;
using namespace otecpp_valuutat;

int main(int argc, char *argv[])
{
  ifstream syote(argv[1]);
  vector<Valuutta> kurssit = lueKurssit(syote);
  kurssit.push_back(Valuutta("PAB", "Panamanian Balboa", 0.9303977627));
  sort(kurssit.begin(), kurssit.end(), Valuutta::lyhenneVrt); // Lajittelu: lyhenne
  cout << "Valuutat lyhenteiden mukaan lajiteltuina:\n";
  for(vector<Valuutta>::size_type i = 0; i < kurssit.size(); ++i)
  {
    cout << kurssit[i] << '\n';
  }
  sort(kurssit.begin(), kurssit.end(), Valuutta::nimiVrt);    // Lajittelu: nimi
  cout << "Valuutat nimien mukaan lajiteltuina:\n";
  for(vector<Valuutta>::size_type i = 0; i < kurssit.size(); ++i)
  {
    cout << kurssit[i] << '\n';
  }
  sort(kurssit.begin(), kurssit.end(), Valuutta::kurssiVrt);  // Lajittelu: kurssi
  cout << "Valuutat kurssien mukaan lajiteltuina:\n";
  for(vector<Valuutta>::size_type i = 0; i < kurssit.size(); ++i)
  {
    cout << kurssit[i] << '\n';
  }
}