#include <iostream>
// murtoluku.h

namespace otecpp_murtoluku {

  class Murtoluku {


    private:
      int os;
      int nim;

      void sievenna();

    public:
      Murtoluku(int os=0, int nim=1);

      // Getterit & Setterit
      int getOs()   const;
      int getNim()  const;
      void setOs(int os);
      void setNim(int nim);

      Murtoluku&  operator++();
      Murtoluku&  operator--();
      Murtoluku   operator++(int);
      Murtoluku   operator--(int);


  }; // Murtoluku

  /*
    Yhteen-, vähennys-, kerto- ja jakolaskun toteuttavat operaattorit 
    operator+, operator-, operator* ja operator/,
    missä kunkin funktion parametrilistat ovat muotoa (const Murtoluku &a, const Murtoluku &b).
  */

  Murtoluku operator+(const Murtoluku &a, const Murtoluku &b);
  Murtoluku operator-(const Murtoluku &a, const Murtoluku &b);
  Murtoluku operator*(const Murtoluku &a, const Murtoluku &b);
  Murtoluku operator/(const Murtoluku &a, const Murtoluku &b);

  std::ostream& operator<<(std::ostream &virta, const Murtoluku &ml);

  


}