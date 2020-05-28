#include <iostream>
// luvut.h


namespace otecpp_luvut {

  class Luku {

    public:
      ~Luku();
      virtual operator double() const;
      virtual operator double() const;

    private:
      // ...
    
  };



  std::ostream& operator<<(std::ostream &virta, const Luku &luku);
  std::ostream& operator<<(std::ostream &virta, const Luku *luku);

}