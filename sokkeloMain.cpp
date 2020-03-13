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

  for(int i=0; i<=200; ++i) {
    
    bool x = s.askella( 1 );
    //cout << "askella palautti " << x << endl;
    cout << s << '\n';
    if(!x) {
      //cout << "Ulkona!\n";
      break;
    } 
  }
 


}