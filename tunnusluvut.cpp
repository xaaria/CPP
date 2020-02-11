#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>

// 1 - tunnusluvut.cpp
// Toteuta ohjelma, joka pyytää käyttäjää antamaan joukon lukuja 
// ja joka laskee ja tulostaa ruudulle annettujen lukujen seuraavat perustavanlaatuiset 
// tilastolliset tunnusluvut. Keskiarvo / Mediaani / Varianssi
// Oletetaan että tyhjän joukon tunnusluvut ovat 0.0

double mean(const std::vector<double>& ns) {
  
  double sum = 0;
  if(ns.size() == 0) { return 0.0; }
  for(std::vector<double>::size_type i=0; i<ns.size(); i++) {
    sum += ns.at(i);
  }
  return sum / ns.size();

}



double median(const std::vector<double>& ns) {

  if(ns.empty()) { return 0; }
  
  // jos ei pariton, keskimmäinen
  if(ns.size() % 2 == 1) {
   return ns.at( (ns.size()/2) );
  } 
  else {
    int middle = (int) (ns.size()/2);
    double sum = ns.at( middle-1 ) + ns.at( middle );
    return sum / 2.0; // [0][1][2][3] => 4/2 => 2 , so return mean of i=2 and 1
  }

}

/*
  kunkin luvun N erotus keskiarvosta korotettuna toiseen potenssiin summattuna ja jettuna lukumäärällä
*/
double variance(const std::vector<double>& ns) {

  // eka tarkastus
  if(ns.empty()) { return 0; }

  const double mean_    = mean(ns);
  double sum = 0.0;

  for(std::vector<double>::size_type i=0; i<ns.size(); i++) {
    sum += pow( ns.at(i) - mean_, 2.0);
  }

  return sum/ns.size();

}


int main() {

  std::vector<double> numbers;
  std::string user_input = "";

  // Kysytään lukuja niin kauan kunnes syöte on "lopeta"

  while(std::cin.good()) {

    numbers.clear();

    std::cout << "Anna luvut välilyönnein eroteltuina: "; 
    getline(std::cin, user_input);

    if(user_input == "lopeta") {
      std::cout << "Ohjelma lopetetaan\n";
      return 0;
    }

    std::istringstream istringstream_(user_input);

    double d;

    while(istringstream_ >> d) {
      //std::cout << "onnistui ja saatiin: " << d << std::endl;
      numbers.push_back(d);
    }

    // jos ei saatu luettua yhtään...
    if(numbers.empty()) {
      std::cout << "Virheellinen syöte!" << std::endl;
      continue; // takaisin alkuun/seuraavalle kierrokselle...
    }

    // Tulosta annetut luvut (siinä järj. kun käyttäjä ne antoi)
    std::cout << "Antamasi luvut olivat:";
    for(std::vector<double>::size_type i=0; i<numbers.size(); i++) {
      std::cout << " " << numbers.at(i);
    }
    std::cout << std::endl;


    // sorttaa
    std::sort(numbers.begin(), numbers.end() );

    std::cout << "  keskiarvo: "  << mean(numbers) << std::endl;
    std::cout << "  mediaani: " << median(numbers) << std::endl;
    std::cout << "  varianssi: " << variance(numbers) << std::endl;
    

  }







  return 0;
}