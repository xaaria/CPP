#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include "jaccard.h"

const bool DE = 1;

namespace otecpp_jaccard {
  



  double jaccard(std::istream& a, std::istream& b, unsigned int k) {

    std::vector<std::string> sanat_a = lueSanat(a);
    std::vector<std::string> sanat_b = lueSanat(b);

    if(DE) std::cout << sanat_a.size() << " | " << sanat_b.size() << std::endl;

    std::set<sanasetti_t> comb_a   = haeKaikkiYhdistelmat(sanat_a, k); // A
    std::set<sanasetti_t> comb_b   = haeKaikkiYhdistelmat(sanat_b, k); // B
    std::set<sanasetti_t> comb_a_2(comb_a);
    std::set<sanasetti_t> comb_b_2(comb_b);
    
    //std::cout << "#" << comb_a_2.size();


    // Union
    std::vector<sanasetti_t> union_;
    std::set_union( comb_a.begin(), comb_a.end(), comb_b.begin(), comb_b.end(), std::back_inserter(union_) );

    if(DE) std::cout << "Union size: " << union_.size() << std::endl;

    // Intersection
    std::vector<sanasetti_t> intersect;
    std::set_intersection(comb_a_2.begin(), comb_a_2.end(), comb_b_2.begin(), comb_b_2.end(), intersect.begin(), cmp );
    if(DE) std::cout << "Intersection size: " << intersect.size() << std::endl;

    double jaccard = static_cast<double>(intersect.size()) / union_.size();

    std::cout << "= Jaccard: " << jaccard << std::endl;

    return jaccard; // (double)union_->size() / 10; //intersect->size();

  }


  bool cmp(const sanasetti_t &a, const sanasetti_t &b) {
    return &a < &b;
  }








  /*
    K‰‰refunktio, jossa hoidetaan rekursiivisen funktiokutsun arvojen talteenotto ja 
    tietorakenteen muuntaminen.
  */
  std::set<sanasetti_t> haeKaikkiYhdistelmat(std::vector<std::string>& sanat, short k) {

    // Yksitt‰inen sanasetti (vektorimuodossa). esim { <AA, BB>, ... }
    std::set<sanasetti_t> ret; // Palautettava arvo
    std::set<std::vector<std::string> > kaikki;
    std::vector<std::string> tulos; // yksitt‰inen kombinaatio!
    


    yhdistelma(sanat, 0, k, tulos, kaikki);

    for(std::set<std::vector<std::string> >::iterator it=kaikki.begin(); it != kaikki.end(); ++it) {
      
      //if(DE) std::cout << "{ ";
      
      std::set<std::string> kombinaatio;

      for( short i=0; i < it->size(); ++i ) {
        //std::cout << it->at(i) << ", ";
        kombinaatio.insert(it->at(i));
      }
      ret.insert( kombinaatio );

      //if(DE) std::cout << " }\n";
    }

    return ret; // Palauta setti sanasettej‰!


  }


  /*
    i = aloituskohta
    k = setin maksimikoko
    koko = nykyinen koko
  */
  void yhdistelma(std::vector<std::string>& sanat, short offset, short max, std::vector<std::string>& tulos, std::set<std::vector<std::string> >& kaikki) {

    if(max == 0) { 
      // Tallenna kutsujassa m‰‰riteltyyn isompaan tulosjoukkoon saatu kombinaatio
      kaikki.insert( tulos );
      return; 
    }

    for (int i=offset; i <= sanat.size() - max; ++i) {
      
      tulos.push_back(sanat.at(i));
      yhdistelma(sanat, i+1, max-1, tulos, kaikki);
      tulos.pop_back(); // poista eka

    }

  }


  std::vector<std::string> lueSanat(std::istream& inp) {

    std::vector<std::string> sanat;
    std::string rivi;
    //

    while( std::getline(inp, rivi, '\n') ) {

      //std::cout << rivi;

      std::istringstream is(rivi);
      std::string sana;

      while(is >> sana) {
        if( std::find(sanat.begin(), sanat.end(), sana ) == sanat.end()) {
          sanat.push_back( sana );
        }
      }
    }
    
    return sanat;

  }
  


}