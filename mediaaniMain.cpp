#include <vector>
#include <iostream>
#include <string>
#include "mediaani.h"

using namespace std;

int main() {


  vector<int> it(5);
  it[0] = 1; it[1] = 8; it[2] = 2; it[3] = 19; it[4] = 3;
  cout << "Mediaani(1, 8, 2, 19, 3): " << otecpp_mediaani::mediaani(it) << '\n';
  it.push_back(6);   // Lisätään perään arvo 6.
  cout << "Mediaani(1, 8, 2, 19, 3, 6): " << otecpp_mediaani::mediaani(it) << '\n';
  vector<string> st(4);
  st[0] = "tammikuu";
  st[1] = "helmikuu";
  st[2] = "maaliskuu";
  st[3] = "marraskuu";
  cout << "Mediaani(\"tammikuu\", \"helmikuu\", \"maaliskuu\", \"marraskuu\"): "
        << otecpp_mediaani::mediaani(st) << '\n';
  st[3] = "maalis";   // Vaihdetaan "marraskuu" --> "maalis".
  cout << "Mediaani(\"tammikuu\", \"helmikuu\", \"maaliskuu\", \"maalis\"): "
        << otecpp_mediaani::mediaani(st) << '\n';

  return 0;
}