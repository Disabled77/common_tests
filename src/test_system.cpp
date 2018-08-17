#include "test_system.hpp"

std::map <std::string, std::vector<std::shared_ptr<ITestFunctor>>>& get_functions()
{
	static std::map <std::string, std::vector<std::shared_ptr<ITestFunctor>>> functions;
	return functions;
}