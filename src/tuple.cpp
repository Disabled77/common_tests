#include <iostream>
#include <string>

#include "test_system.hpp"



TEST_FUNCTION(Tuple, general){

  const int checkInt = 2;
  const double checkDouble = 34.2;

  std::tuple<int,double> tuple{ checkInt, checkDouble };
  EXPECT_EQ(checkInt, std::get<0>(tuple));
  EXPECT_EQ(checkDouble, std::get<1>(tuple));
}
