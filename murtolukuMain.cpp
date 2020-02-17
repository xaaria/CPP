#include <iostream>
#include "murtoluku.h"

using namespace std;
using otecpp_murtoluku::Murtoluku;

int main(int argc, char *argv[]) {


  Murtoluku ml_a(12,5);
  Murtoluku ml_b(0,1);

  Murtoluku ml_c(12,-15);
  Murtoluku ml_d(-3,0);

  std::cout << ml_a / ml_b << std::endl;
  std::cout << ml_c / ml_d << std::endl;
  std::cout << ml_d / ml_c << std::endl;
  /*std::cout << ml_b << std::endl;
  std::cout << ml_c << std::endl;
  std::cout << ml_d << std::endl;
  */



  /* --- */


  Murtoluku mlt[6] = {Murtoluku(3, 9), Murtoluku(2, -10), Murtoluku(0, 4),
                        Murtoluku(-2, 0), Murtoluku(), Murtoluku(5)};
  cout << "Luvut:";
  for(int i = 0; i < 6; ++i)
  {
    cout << " " << mlt[i];
  }
  cout << endl;
  for(int i = 1; i < 4; ++i)
  {
    cout << mlt[i-1] << " + " << mlt[i] << " = " << mlt[i-1] + mlt[i] << '\n';
    cout << mlt[i-1] << " - " << mlt[i] << " = " << mlt[i-1] - mlt[i] << '\n';
    cout << mlt[i-1] << " * " << mlt[i] << " = " << mlt[i-1] * mlt[i] << '\n';
    cout << mlt[i-1] << " / " << mlt[i] << " = " << mlt[i-1] / mlt[i] << '\n';
  }
  cout << mlt[0] << "++ = ";
  cout << mlt[0]++ << '\n';
  cout << mlt[0] << "-- = ";
  cout << mlt[0]-- << '\n';
  cout << "++" << mlt[0] << " = ";
  cout << ++mlt[0] << '\n';
  cout << "--" << mlt[0] << " = ";
  cout << --mlt[0] << '\n';
}