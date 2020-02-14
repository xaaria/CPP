#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include "hirsipuu.h"
// hirsipuu.cpp

const bool DE = true;

namespace otecpp_hirsipuu {

  /* Varsinainen peli */
  void hirsipuu(const std::string& sanatiedosto, unsigned int x, unsigned int maxVirheet) {


    bool running = true;
    bool gameOn = true;
    std::set<char> guessed; // setin koko on yhteisarvausten määrä!
    unsigned int wrong_guesses = 0;
    std::vector<std::string> words = haeSanatTiedostosta(sanatiedosto);

    std::string word = words.at( x % words.size() ); // älä muuta!

    std::string command_line, command; 
    char letter;
    std::istringstream iss;


    do {

      /* Tulosta pelin tilanne */
      if(gameOn) {
        std::cout << "Arvattava sana on " << otecpp_hirsipuu::haeSananTilanne(word, guessed) << ", vielä "<< maxVirheet-wrong_guesses << " virhettä jäljellä" << std::endl;
      }
      iss.clear();
      command.clear(); 
      /* --- */

      //std::cout << ">>> ";
      getline(std::cin, command_line);

        iss.str(command_line); // aseta sis.
        iss >> command;

        //std::cout << "\tKOMENTO " << command << std::endl;
      

        if(command == "kirjain") {

          if(iss >> letter) {
            if(DE) {
              //std::cout << " veikattiin: " << letter << std::endl;
            }
            // palauttaa parin <iteraattori, bool>, jossa totuusarvo, että lisäättiinkö [false = ei, oli jo]
            // http://www.cplusplus.com/reference/set/set/insert/
            if(onkoKirjainSanassa(letter, word) == false || guessed.insert(letter).second == false) {
              // Virheellinen arvaus! myös silloin jos kirjainta veikataan uudelleen
              ++wrong_guesses;
              //std::cout << "(#!) " << wrong_guesses << std::endl;
            } else {
              // Kirjain lisätiin. Virheiden määrää ei kasvatettu.
              //std::cout << "hyvä arvaus!" << std::endl;
            }
          } else {
           // std::cout << "(!) fail" << std::endl;
          }
          

        }

        else if(command == "sana") {
           
          // lue jatko... eli veikattava sana
          if(iss >> command) {
            if(command == word) {
              haeLopetusviesti(word, true);
              gameOn = false; // aktiivinen peli loppuu, ei itse komentojen luku
              running = true; 
              continue;
            }  
            else {
              /*
                os arvattu sana ei täsmää edes yhdenkin kirjaimen osalta, 
                on arvaus kokonaisuudessaan virheellinen. 
                Tällöin virheellisten arvausten lukumäärää kasvatetaan yhdellä 
              */
             wrong_guesses++;

            }
          }

        }

        else if(command == "lopeta") {
          // haeLopetusviesti(word); // ei sanaa tässä tapauksessa
          running = false;
          continue;

        }

        else if(command == "uusi") {
          // std::cout << "[u] ";
          unsigned int x_, max_virh;
          iss >> x_;
          iss >> max_virh;

          if(! iss.fail() ) {
            
            // Aloittaa uuden pelin, eli vaihtaa muuttujat. Jatkaa sitten tuttuun tapaan
            word = words.at( x_ % words.size() );
            gameOn = true; // pelin tilanne heti alkuun
            x = x_; // turha?
            wrong_guesses = 0;
            guessed.clear();
            maxVirheet = max_virh;
            running = true; // turha?

          } else { 
            //std::cout << "lukuvirhe!"; 
          }
          continue;
        }

        else {
          std::cout << "Tuntematon komento\n";
        }


      // huom. >. Tasan saman verran sallitaan. Tällöin enää sanan arvaaminen kelpaa.
      if(wrong_guesses > maxVirheet) {
        running = false;
        haeLopetusviesti(word);
      } else {
        //
      }
      

    } while(running);


  }




  /* Palauttaa vektorin jossa tiedoston sanat siinä järj. kun ne olivat tiedostossa  */
  std::vector<std::string> haeSanatTiedostosta(const std::string& sanatiedosto) {

    std::vector<std::string> words;
    std::string w;
    std::ifstream ifs(sanatiedosto.c_str(), std::ifstream::in); // lukumoodi

    // jos luettavissa
    if(ifs) {
      while( getline(ifs, w, '\n') ) {
        words.push_back(w);
      }
    }

    // lopuksi
    return words;

  }

  bool onkoKirjainSanassa(const char kirjain, const std::string sana) {
    return sana.find(kirjain) != std::string::npos; 
  }



  /*
  Palauttaa merkkijonon muodossa a_____, jossa parametrin sana paikalla on viiva _ jos 
  kyseissä paikassa esiintyvä kirjain ei ole arvattujen (param. arvaukset) joukossa.
  */
  std::string haeSananTilanne(const std::string& sana, const std::set<char>& arvaukset) {
    std::string x = "";
   
    for(std::string::size_type i = 0; i < sana.size(); ++i) {
      char c = sana.at(i);
      //std::cout << c << std::endl;
      if( arvaukset.find(c) != arvaukset.end() ) {
        x.insert( x.end(), 1, c );
      } else {
        x.append("_");
      }
    }
    return x;
  }


  void haeLopetusviesti(const std::string& sana, const bool victory) {
    if(victory) {
      std::cout << "Voitit,";
    } else {
      std::cout << "Hävisit,";
    }
    std::cout << " sana oli " << sana << "!\n";
  }

} // end of namespace 


int main() {

  otecpp_hirsipuu::hirsipuu("words.txt", 2, 5);

}