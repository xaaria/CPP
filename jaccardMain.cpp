#include <iostream>
#include <algorithm>
#include <sstream>
#include "jaccard.h"

using namespace otecpp_jaccard;

const int K = 2;

const std::string A = "no senator or representative shall during the time for which he was elected be appointed to any civil office under the authority of the united states which shall have been created or the emoluments whereof shall have been encreased during such time and no person holding any office under the united states shall be a member of either house during his continuance in office";
const std::string B = "the senators and representatives shall receive a compensation for their services to be ascertained by law and paid out of the treasury of the united states they shall in all cases except treason felony and breach of the peace be privileged from arrest during their attendance at the session of their respective houses and in going to and returning from the same and for any speech or debate in either house they shall not be questioned in any other place";

const std::string A2 = "huomisen s‰‰ on hyv‰";
const std::string B2 = "ihan tosi oot s‰‰ ihan hyv‰";

int main() {


  std::istringstream text_a(A2);
  std::istringstream text_b(B2);

  std::cout << otecpp_jaccard::jaccard(text_a, text_b, K) << std::endl;
  


  return 0;
}