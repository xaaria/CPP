#include <iostream>
#include <cmath>

namespace otecpp_rakenne {

  template<typename IT> void rakenne(IT alku, IT loppu) {

    // Askella alkiojoukon alkiot l�pi alusta loppuun iteraattorilla.
    int i = -1; // rakenteen indeksi
    const int alku_koko = sizeof(*alku);

    //while( &(*(alku++)) < &(*loppu) ) {
    while( reinterpret_cast<char*>(&(*(alku++))) != reinterpret_cast<char*>(&(*loppu)) ) {

      i++;
      //std::cout << &(*(alku)) << " arvo: " << *alku << " <|> " << &(*loppu) << " arvo: " << *loppu << std::endl;
      
      // Kunkin alkion kohdalla laske nykyisen alkion sek� sit�
      // edelt�v�n alkion osoitteiden erotus (jos edelt�v� alkio on olemassa eli i > 0)
      // Case 0
      if(i == 0) { std::cout << "[0";  continue; } 

      // Varsinainen koodi
      // Laske erotus
      IT iter_copy = alku;  iter_copy--;
      const int diff = reinterpret_cast<char*>(&(*alku)) - reinterpret_cast<char*>(&(*(iter_copy) ));  // [X]...[Y]. Y-X
      //std::cout << "\tMuistipaikkojen erotus: " << diff << std::endl; 

      /*
        Case 1
        Jos nykyisen eli indeksin i ja sit� edelt�v�n eli 
        indeksin i-1 alkion osoitteiden erotus != sizeof(*alku), on kaksi erillist� tapausta:
      */
      if(diff != alku_koko) {

        // T�m�n tapauksen j�lkeen on viel� kaksi erillist� tapausta
        // "Jos edelt�v�n indeksin i-1 ja sit� edelt�v�n indeksin i-2 alkioiden osoitteiden erotus on sizeof(*alku) ..."
        IT iter_copy_alku   = alku;
        IT iter_copy_alku_2     = alku;
        iter_copy_alku--;   // jotta saadaan i-1
        iter_copy_alku_2--; iter_copy_alku_2--;  // ... i-2;
        
        //const int diff_2 = &(*iter_copy_alku) - &(*iter_copy_alku_2);
        // Eli erotus i-1 miinus i-2
        const int diff_2 = reinterpret_cast<char*>(&(*iter_copy_alku)) - reinterpret_cast<char*>(&(*iter_copy_alku_2));

        // 1 A
        if( diff_2 == alku_koko ) {
          std::cout << "..." << i-1 << "] --> [" << i;
        } else {
          // 1 B. "Muuten tulosta muotoa "] --> [i" oleva merkkijono"
          std::cout << "] --> [" << i;
        }
      } 
      
      // Case 2. Huom! Mahdollinen casen 1 lis�ksi!
      // Lis�ksi jos nykyinen alkio on koko koko alkiojoukon viimeinen alkio ...
      //if( &(*alku) == &(*loppu) ) {
      if( reinterpret_cast<char*>(&(*alku)) == reinterpret_cast<char*>(&(*loppu)) ) {
        //std::cout << &(*(alku)) << " arvo: " << *alku << " <|> " << &(*loppu) << " arvo: " << *loppu << std::endl;
        //std::cout << diff << "sizeof *alku: " << alku_koko << std::endl; 

        // 2 A
        if( diff == alku_koko ) {
          std::cout << "..." << i << "]\n";
        } else {
          // 2 B
          std::cout << "]\n";
        }

      }
        
      
    }
  }
  


}