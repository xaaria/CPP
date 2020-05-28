#include <iostream>
#include <string>
#include <sstream>      // std::istringstream
#include <istream>
#include "valuutat.h"
#include <stdlib.h>

namespace otecpp_valuutat {


	Valuutta::Valuutta(std::string lyhenne, std::string nimi, double kurssi) : lyhenne_(lyhenne), nimi_(nimi), kurssi_(kurssi) {}

	std::string Valuutta::lyhenne() const {
		return this->lyhenne_;
	}
	std::string Valuutta::nimi() const {
		return this->nimi_;
	}
	double Valuutta::kurssi() const {
		return this->kurssi_;
	}

	Valuutta::~Valuutta() {}
	//



	std::vector<Valuutta> lueKurssit(std::istream& syote) {

		std::vector<Valuutta> v; // ei sulkuja t�h�n!
		std::string rivi;

		// Lue rivi kerrallaan
		while(getline(syote, rivi)) {

			std::string lyhenne, nimi;
			std::string str; //
			double kurssi;
			std::vector<std::string> tmp; // arvot v�liaikaisesti t�nne (nimi/lyhenne/kurssi)

			std::istringstream ist (rivi);
			while(getline(ist, str, '\t')) {
					tmp.push_back(str);
					//std::cout << str << " | ";
			}

			// Muutetaan viimeinen (i=2) merkkijono doubleksi, eli kurssi.
			// Kiitokset: http://www.geeksforgeeks.org/converting-strings-numbers-cc/
			std::stringstream convert(tmp[3]);
			convert >> kurssi;

			v.push_back( Valuutta(tmp[0], tmp[1], kurssi) );
		}


		return v;
	}

	bool Valuutta::lyhenneVrt(const Valuutta& a, const Valuutta& b) {
		return a.lyhenne() < b.lyhenne();
	}
	
	
	bool Valuutta::nimiVrt(const Valuutta& a, const Valuutta& b) {
		return a.nimi() < b.nimi();
	}
	
	// Vertailu valuutan kurssin mukaan. Jos sama, palautetaankin lyh. perusteella
	bool Valuutta::kurssiVrt(const Valuutta& a, const Valuutta& b) {
		if( a.kurssi() == b.kurssi() ) {
			return lyhenneVrt(a, b);
		}
		return a.kurssi() < b.kurssi();
	}


	std::ostream& operator<<(std::ostream& out, const Valuutta& v) {
		out << v.lyhenne() << " " << v.nimi() << " " << v.kurssi(); 
		return out;
	}

}
