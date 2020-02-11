#include <iostream>
#include <string>
#include <vector>
#include "lajitellut.h"

using namespace std;
using otecpp_lajitellut::lajitellut;

int main(int argc, char *argv[]) {
  vector<string> mjt = lajitellut(argc - 1, argv + 1); // Hypätään alkion argv[0] yli
  for(vector<string>::size_type i = 0, koko = mjt.size(); i < koko; ++i)
  {
    cout << mjt[i] << '\n';
  }
  return 0;
}