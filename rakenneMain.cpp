#include <deque>
#include <iostream>
#include <list>
#include <vector>
#include "rakenne.h"

using namespace std;

int main()
{
  vector<double> v(1000); //v(10000);
  deque<char> d;
  list<int> l(10);
  for(int i = 0; i < 5000; ++i)
  {
    d.push_back(0);
    d.push_front(0);
  }
  
  //cout << "vector-taulukon rakenne:\n";
  //otecpp_rakenne::rakenne(v.begin(), v.end());

  //return 0;

  cout << "deque-jonon rakenne:\n";
  otecpp_rakenne::rakenne(d.begin(), d.end());
  cout << "list-listan rakenne:\n";
  otecpp_rakenne::rakenne(l.begin(), l.end());
}