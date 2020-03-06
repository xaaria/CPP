// sokkeloMain.cpp
#include <fstream>
#include <iostream>
#include <stack>
#include <utility>  // pair
#include "sokkelo.h"

using namespace std;
using otecpp_sokkelo::Sokkelo;


int main() {

  ifstream td("sokkelo.txt");
  Sokkelo s(td);

  cout << s << '\n';

  s.askella( 1 );

}