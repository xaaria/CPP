#include <iostream>
#include <sstream>
#include <string>


namespace otecpp_rot13stream {

  class Rot13Stream : public std::ostringstream {

    public:
      Rot13Stream(const std::string& s);
      
      Rot13Stream& operator<<(char c);
      Rot13Stream& operator<<(const std::string& s);
      Rot13Stream& operator<<(const char* s);
      Rot13Stream& operator<<(int i);

    private:
      // ...
  };



  char rot13(const char c);
  std::string rot13(const std::string s);
  
}