#include <vector>
#include <string>
#include <iostream>
#include "lajitellut.h"
// lajitelut.cpp

namespace otecpp_lajitellut {
  
  /* suorittaa yksinkertaisen bubblesortin */
  std::vector<std::string> lajitellut(unsigned int lkm, char* mjt[]) {

    std::vector<std::string> sanat;
    for(unsigned int i=0; i<lkm; i++) {
      std::string temp( mjt[i] );
      sanat.push_back( temp );
      //std::cout << "+ " << temp << " | " << sanat.size() << std::endl;
    }

    if(sanat.size() <= 1) { return sanat; }

    // Sorttaa, jos koko >= 2
    std::vector<std::string>::size_type end = sanat.size(); 
    bool swapsDone = false;

    do {
      swapsDone = false;
      for(std::vector<std::string>::size_type i=0; i < end-1; i++ ) {
        
        std::string* a = &(sanat.at(i));
        std::string* b = &(sanat.at(i+1));

        //std::cout << "vertaillaan " << *a << " <> " << *b << std::endl;

        if( (*b).compare(*a) < 0) {
          // std::cout << "\t" << *b << " pitäisi olla ennen " << *a << std::endl;
          
          std::string temp = *a;  *a = *b;  *b = temp;
          swapsDone = true;

        }
      }

    } while(swapsDone != false);

    

  }



}



