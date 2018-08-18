#include <iostream>
#include <exception>
#include <string>

#include "test_system.hpp"

int summ1(int first, int second){
   return first + second;
}
TEST_FUNCTION(POINTER_TO_FUNCTION, c_style_ptr){
    
   int(*summ)(int, int) = summ1;
   int result = summ(1, 2);   
   EXPECT_EQ(result, int(3));
}

