#include <iostream>
#include <sstream>
#include <string>
#include "otevector.h"

using namespace std;
using otecpp_otevector::OteVector;

int main()
{
  OteVector<double> dt(10);
  OteVector<string> st(10);

  dt[1] = 90.9;
  //cout << "koko:" << dt.getKoko() << "dt(1) " << dt[1]; 
  
  for(int i = 0; i < 10; ++i)
  {
    dt[i] = i + 0.5;
    ostringstream oss;
    oss << "Arvo " << i << ": ";
    st[i] = oss.str();          // Merkkijono "Arvo i: ".
  }
  // Tulostusilmukassa testataan samalla kopiorakenninta ja asetusoperaattoria
  
  for(int i = 0; i < 10; ++i)
  {
    OteVector<double> dt2(dt);  // dt2 kopiorakennetaan samanlaiseksi kuin dt

    //cout << "dt[] ja dt2[] " << dt[i] << " / " << dt2[i] << endl;

    // Kaatuu tähän? --- Koko ei riitä?

    OteVector<string> st2(i);
    st2 = st = st2 = st = st;   // st2 asetetaan samanlaiseksi kuin st
    cout << st2[i] << dt2[i] << endl;
  }
}