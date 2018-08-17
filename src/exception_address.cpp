#include <iostream>
#include <exception>
#include <string>

#include "test_system.hpp"
TEST_FUNCTION(Exception, throw_same_address){
    size_t error0_address = 0;
    try{
        throw std::logic_error("");
    }
    catch (const std::logic_error& error0){
        error0_address = reinterpret_cast<size_t>(&error0);
        try{
            throw;
        }
        catch(const std::logic_error& error1){
            const size_t error1_address = reinterpret_cast<size_t>(&error1);
            EXPECT_EQ(error0_address, error1_address);
        }
    }
}

TEST_FUNCTION(Exception, throw_different_address){
    size_t error0_address = 0;
    try{
       throw std::logic_error("");
    }
    catch (const std::logic_error& error0){
        error0_address = reinterpret_cast<size_t>(&error0);
        try{
            throw error0;
        }
            catch(const std::logic_error& error1){
            const size_t error1_address = reinterpret_cast<size_t>(&error1);
            EXPECT_NE(error0_address, error1_address);
        }
    }
}

//TEST_FUNCTION(Exception, rethrow){
//    size_t basic_address = 0;
//    std::exception_ptr exception_ptr;

//    try{
//        throw std::logic_error("");
//    }
//    catch (const std::logic_error& error0){
//        exception_ptr = std::current_exception();
//        basic_address = reinterpret_cast<size_t>(&exception_ptr);

//        try{
//            std::rethrow_exception(exception_ptr);
//        }
//        catch(const std::logic_error&){
//            std::exception_ptr rethrow_exception_ptr1 = std::current_exception();
//            const size_t rethrow_address = reinterpret_cast<size_t>(&rethrow_exception_ptr1);
//            EXPECT_EQ(basic_address, rethrow_address);
//        }

//        try{
//            throw std::logic_error("second");
//        }
//        catch(const std::logic_error& e){
//            const std::exception_ptr new_exception_ptr = std::current_exception();
//            const size_t new_address = reinterpret_cast<size_t>(&new_exception_ptr);
//            EXPECT_NE(basic_address, new_address);
//        }
//    }
//}
