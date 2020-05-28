#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>


namespace otecpp_jaccard {
  
  typedef std::set<std::string> sanasetti_t;


  bool cmp(const sanasetti_t &a, const sanasetti_t &b);

  /*
    Laskee Jaccard-arvon tekstien A ja B välillä. K kertoo sanasettien koon
  */
  double jaccard(std::istream& a, std::istream& b, unsigned int k = 1);
  

  std::set<sanasetti_t> haeKaikkiYhdistelmat(std::vector<std::string>& sanat, short k=2);

  /*
    Luo kaikki mahdolliset sanasetit kooltaan K. Sanojen oletetaan olevan uniikkeja
    parametissa sanat.

    i kertoo rekursiolle mistä indeksistä aloitetaan.

    return: { {a,b}, {a,c}, ... }
  */
  void yhdistelma(std::vector<std::string>& sanat, short i, short max, std::vector<std::string>& tulos, std::set<std::vector<std::string> >& kaikki); 


  /*
    Apufunktio sanojen lukuun standardisyötevirrasta.
    Palauttaa VEKTORIN uniikkeja sanoja.
  */
  std::vector<std::string> lueSanat(std::istream& inp);


}