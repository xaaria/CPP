#include <iostream>

namespace otecpp_rakenne {

  template<typename IT> void rakenne(IT alku, IT loppu) {

    // Askella alkiojoukon alkiot läpi alusta loppuun iteraattorilla.
    int i = -1; // rakenteen indeksi

    int alku_koko = sizeof(*alku);
    //std::cout << alku_koko;

    //while( &(*(alku++)) < &(*loppu) ) {
    while( reinterpret_cast<char*>(&(*(alku++))) < reinterpret_cast<char*>(&(*loppu)) ) {

      i++;
      //std::cout << &(*(alku)) << " arvo: " << *alku << " <|> " << &(*loppu) << " arvo: " << *loppu << std::endl;
      
      // Kunkin alkion kohdalla laske nykyisen alkion sekä sitä
      // edeltävän alkion osoitteiden erotus (jos edeltävä alkio on olemassa eli i > 0)
      // Case 0
      if(i == 0) { std::cout << "[0";  continue; } 

      // Varsinainen koodi
      // Laske erotus
      IT iter_copy = alku;  iter_copy--;
      //const int diff = (&(*alku)) - &(*(iter_copy) );
      const int diff = reinterpret_cast<char*>(&(*alku)) - reinterpret_cast<char*>(&(*(iter_copy) ));  // [X]...[Y]. Y-X
      //std::cout << "\tMuistipaikkojen erotus: " << diff << std::endl; 

      // Case 1
      if(diff != alku_koko) {

        // Tämän tapauksen jälkeen on vielä kaksi erillistä tapausta
        IT iter_copy_alku     = alku;
        IT iter_copy_alku_2   = alku;
        iter_copy_alku--;   // jotta saadaan i-1
        iter_copy_alku_2--; iter_copy_alku_2--;  // ... i-2;
        
        //const int diff_2 = &(*iter_copy_alku) - &(*iter_copy_alku_2);
        const int diff_2 = reinterpret_cast<char*>(&(*iter_copy_alku)) - reinterpret_cast<char*>(&(*iter_copy_alku_2));

        // 1 A
        if( diff_2 == alku_koko ) {
          std::cout << "..." << i-1 << "] --> [" << i;
        } else {
          // 1 B
          std::cout << "] --> [" << i;
        }
      } 
      
      // Case 2. Huom! Mahdollinen casen 1 lisäksi!
      // Lisäksi jos nykyinen alkio on koko koko alkiojoukon viimeinen alkio ...
      
      if( &(*alku) == &(*loppu) ) {
      //if( reinterpret_cast<char*>(&(*alku)) == reinterpret_cast<char*>(&(*loppu)) ) {
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