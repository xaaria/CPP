#include <iostream>
#include "vektori.h"
//#include "poikkeukset.h"

using namespace std;
using namespace otecpp_vektori;
using namespace otecpp_poikkeukset;

int main() {

  const int koko = 3;
  Vektori<int, koko> v;
  v[0] = 2; v[1] = 4; v[2] = 4;
  const Vektori<int, koko> &vc = v;
  Vektori<int, koko> v2;
  v2[0] = 2; v2[1] = -4; v2[2] = -4;
  cout << "v: " << vc << " ja v2: " << v2 << endl;
  cout << "v + v2: " << vc + v2 << endl;
  cout << "v - v2: " << vc - v2 << endl;
  cout << "v.pisteTulo(v2): " << vc.pisteTulo(v2) << endl;
  cout << "Pituus: " << vc.pituus() << endl;
  Vektori<int, 10> v3;
  for(size_t i = 0; i <= v3.n; ++i) // huom! 0-10 ei 0-9!
  {
    try
    {
      v3[i] = i;
    }
    catch(exception& e)
    {
      cout << e.what() << endl;
      break;
    }
  }
  cout << "v3: " << v3 << endl;

}