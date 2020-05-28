#include <iostream>
#include <string>
#include <istream>
#include <vector>

namespace otecpp_valuutat {

  class Valuutta {

    private:
      std::string lyhenne_;
      std::string nimi_;
      double kurssi_;

    public:

      Valuutta(std::string lyhenne, std::string nimi, double kurssi);

      // ei get-etuliitettä!
      std::string lyhenne() const;
      std::string nimi() const;
      double kurssi() const;

      ~Valuutta();

      // Vertaimet
      static bool lyhenneVrt (const Valuutta& a, const Valuutta& b);
      static bool nimiVrt    (const Valuutta& a, const Valuutta& b);
      static bool kurssiVrt  (const Valuutta& a, const Valuutta& b);
  };


  std::vector<Valuutta> lueKurssit(std::istream& syote);

  std::ostream& operator<<(std::ostream& out, const Valuutta& v);


}
