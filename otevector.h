#include <iostream>

namespace otecpp_otevector {


  template<typename T> class OteVector {
    

    private:
      unsigned int koko;
      T* taulu;

    public:
      OteVector(unsigned int koko); /* : koko(koko), taulu(new T[koko]) { } */
      OteVector(const OteVector& v); // kopiorakennin
      ~OteVector();

      unsigned int getKoko() const;
      T* getTaulu() const;
      
      T& operator[](unsigned int i); 
      
      const T& operator[](unsigned int i) const;

      OteVector<T>& operator=(const OteVector<T>& otevec);  

  };


  /* Luokan toteutus samassa tiedostossa! */

  template<typename T> unsigned int   OteVector<T>::getKoko() const  { return this->koko; }
  template<typename T> T*             OteVector<T>::getTaulu() const { return this->taulu; }

  template<typename T> OteVector<T>::~OteVector() { delete [] this->taulu; }

  template<typename T> OteVector<T>::OteVector(unsigned int koko) : koko(koko), taulu(new T[koko]) {
    //
  }

  // Kopiorakennin
  template<typename T> OteVector<T>::OteVector(const OteVector<T>& v) : koko(v.getKoko()), taulu(new T[v.getKoko()]) {
    // Kopioi viitteestä v ov:hen taulukon arvot
    for(unsigned int i=0; i<v.getKoko(); ++i) {
      //std::cout << v[i] << "\n";
      (*this)[i] = v[i];
      //std::cout << (*this)[i] << "\n";
    } 
  }

  /*
    Lisää asetusoperaattori, joka tarvittaessa vapauttaa aiemman oman taulukon, 
    varaa sen tilalle uuden ja kopioi siihen toisen OmaVector-olion taulukon alkiot.
    Muista varautua itseasetuksen mahdollisuuteen!
  */
  template<typename T> OteVector<T>& OteVector<T>::operator=(const OteVector<T>& vec) {
    
    // jos ei itseisasetusta. Vertailee osoitteita(!)
    if(this != &vec) {
      
      // siirrä otevecin arvot uuteen dyn. taulukkoon
      delete [] this->taulu; // vapauta vanha
      T* uusi = new T[vec.getKoko()];
      //std::cout << "ei itseisasetus | uusi koko " << vec.getKoko() << std::endl;

      // kopioi this:iin vecistä arvot
      for(unsigned int i=0; i<vec.getKoko(); ++i) {
        uusi[i] = vec[i];
        //std::cout << uusi[i] << " <= " << vec[i] << std::endl; 
      }

      
      // -- delete [] this->taulu; // vapauta vanha
      this->taulu   = uusi;
      this->koko    = vec.getKoko(); // päivitä koko

    } else {
      //std::cout << "(its.asetus)\n";
    }

    //std::cout << "this.koko " << this->koko << std::endl;
    return *this;


  }  



  template<typename T> T& OteVector<T>::operator[](unsigned int i) {
    return this->taulu[i];
  }

  template<typename T> const T& OteVector<T>::operator[](unsigned int i) const {
    return this->taulu[i];
  }

}
















