#include <iostream>
#include <string>

#include "test_system.hpp"
#include "tuple.hpp"

TEST_FUNCTION(Tuple, general){

  const int checkInt = 2;
  const double checkDouble = 34.2;

  std::tuple<int,double> tuple{ checkInt, checkDouble };
  EXPECT_EQ(checkInt, std::get<0>(tuple));
  EXPECT_EQ(checkDouble, std::get<1>(tuple));
}


int sum(const int left, const int right){
  return left + right;
}
double add(int a, double b) { return a+b; }
std::tuple<int,double> some_tuple{2, 34.2};

TEST_FUNCTION(Tuple, with_function){

  const int left = 2;
  const int right = 4;

  std::tuple<int,int> tuple{ left, right };
  //const int sum = applyTuple(sum, tuple); doesnt work
  const auto sum = applyTuple(add, tuple); // work
  EXPECT_EQ(sum, int(6));
}

template<typename T1, typename T2>
T1 multiply(const T1& left, const T2&& right){
  return left * right;
};


