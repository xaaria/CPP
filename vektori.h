#ifndef VEKTORI_H
  #define VEKTORI_H

#include <iostream>
#include <cmath>
#include <sstream>
#include "poikkeukset.h"

using namespace otecpp_poikkeukset;

namespace otecpp_vektori  {

  /* toteutus samassa tiedostossa */

  // size_t koko on tÃ¤ssÃ¤ ERIKOISTAMINEN (specialization), eli
  // tÃ¤tÃ¤ geneeristÃ¤ luokkaa kÃ¤ytetÃ¤Ã¤n silloin kun alustus Vektori<...> 
  // on muotoa T ja size_t
  // Esim Vektori<Double, "kissa"> EI kÃ¤yttÃ¤isi tÃ¤tÃ¤ pohjaa

  template<typename T, size_t koko> class Vektori {

    private:
      T* arvot;

    public:

      const size_t n; // = koko; // eli n = <koko>

      Vektori() {
        this->arvot = new T[koko];
      }

      


      // Kuormitetut operaattorit, ks. kalvot s.99
      T& operator [](unsigned int i) throw(LaitonIndeksi) {

        if(i >= this->n) { 
          std::stringstream ss;
          ss << i;
          throw LaitonIndeksi(ss.str()); 
        }
        return this->arvot[i];

      }

      const T& operator [](unsigned int i) const throw(LaitonIndeksi) {
        if(i >= this->n) { 
          std::stringstream ss;
          ss << i;
          throw LaitonIndeksi(ss.str()); 
        }
        return this->arvot[i];
      }


      double pituus() const {
        double sum = 0.0;
        for(unsigned int vi=0; vi<this->n; ++vi) {
          sum += std::pow( (*this)[vi], 2);
        }
        return std::sqrt(sum);
      }

      /*
        Kertoo kunkin kahden indeksin arvot keskenÃ¤Ã¤n. esim. A[i] * B[i] ...
        Paluuarvo on nÃ¤iden arvojen summa, double.
      */
      template<typename U> double pisteTulo(const Vektori<U, koko> &b) const {

        double tulojensumma = 0.0;
        for(unsigned int vi=0; vi<koko; ++vi) {
          tulojensumma += (*this)[vi] * b[vi];
        }
        return tulojensumma;

      }


      /*
        Saa parametrikseen vakioviitteen Vektori<U, koko>-olioon, missÃ¤ taustalla 
        on oletus, ettÃ¤ vaikka U ei vÃ¤lttÃ¤mÃ¤ttÃ¤ ole sama kuin T, 
        voidaan U- ja T-arvoja laskea yhteen.
      */
      template<typename U> Vektori operator+(const Vektori<U, koko> &b) const {

        Vektori<T, koko> uusi;

        for(unsigned int vi=0; vi<koko; ++vi) {
          uusi[vi] = b[vi] + (*this)[vi];
        }
        return uusi;

      }

      template<typename U> Vektori operator-(const Vektori<U, koko> &b) const {

        Vektori<T, koko> uusi;

        for(unsigned int vi=0; vi<b.n; ++vi) {
          uusi[vi] = (*this)[vi] - b[vi];
        }
        return uusi;

      }


      

  };

  // Luokan ulkopuolelle

  /*
    Tulostaa vektorin v arvot muodossa "[v[0], ..., v[n-1]]" 
    eli hakasulkeiden sisÃ¤llÃ¤ toisistaan pilkuilla ja vÃ¤lilyÃ¶nneillÃ¤ eroteltuina.
    Esim: [2, 4, 1]
  */
  template<typename T, size_t koko> std::ostream& operator<<(std::ostream& out, const Vektori<T, koko>& v) {
    out << "[";

    for(unsigned int i=0; i<v.n; ++i) {
      out << v[i];
      if(i != v.n-1) {
        out << ", ";
      }
    } 

    out << "]";
    return out;
  }
  

}
#endif