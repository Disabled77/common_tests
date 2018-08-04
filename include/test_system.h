#pragma once
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <regex>

#include <stdint.h>

//#if BOOST_OS_WINDOWS
//#define CURRENT_PRETTY_FUNCTION __FUNCTION__ 
//#elif BOOST_OS_LINUX
#define CURRENT_PRETTY_FUNCTION __PRETTY_FUNCTION__
//#endif

#ifndef NAME_WITH_LINE
	#define NAME_WITH_LINE1(name, line) name##line
	#define NAME_WITH_LINE(name, line) NAME_WITH_LINE1(name, line)
#endif


//  Windows
//#if BOOST_OS_WINDOWS
#include <intrin.h>
size_t rdtsc()
{
	return static_cast<size_t>(__rdtsc());
}
//#elif BOOST_OS_LINUX

/*size_t rdtsc()
{
	unsigned int lo, hi;
	__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t) hi << 32) | lo;
}
//#endif*/

namespace std
{

template <typename T>
string to_string(const std::vector<T>& vector)
{
	std::string result;
	static constexpr size_t MAGIC_NUMBER = 10;
	for(size_t i = 0; i < vector.size() && i < MAGIC_NUMBER; ++i) {
		result.append(vector.at(i)).append("|");
	}
	return result;
}

string to_string(const std::string& row)
{
	if(row.empty()) {
		return "";
	}
	return row + " ";
}

string to_string(const bool& flag)
{
	return flag ? "true " : "false ";
}


string to_string(void* address)
{
	return std::to_string(std::uintptr_t(address));
}

template <typename T, size_t numberOfElements>
string to_string(const T(&array)[numberOfElements])
{
	return std::string(array, numberOfElements);
}

} //namespace std

bool& test_flag()
{
	static bool testFlag = true;
	return testFlag;
}

bool& all_test_flag()
{
	static bool allTests = true;
	return allTests;
}

template <typename T1, typename T2>
constexpr bool CONTENT_EQUAL(T1&& firstCond, T2&& secondCond) 
{
  return firstCond == secondCond ? true: false;
};

template <typename T1, typename T2>
void ASSERT_EQ_IMPL(const std::string functionName, T1&& first, T2&& second)
{
	bool equal = CONTENT_EQUAL(std::forward<T1>(first), std::forward<T2>(second));
	if(!equal) {
		throw std::logic_error(functionName + " FAILED. first : " + std::to_string(first) + ", second : " + std::to_string(second));
	};
}

template <typename T1, typename T2>
void ASSERT_EQ(T1&& first, T2&& second)
{
	ASSERT_EQ_IMPL(CURRENT_PRETTY_FUNCTION, std::forward<T1>(first), std::forward<T2>(second));
}

template <typename T1, typename T2>
void EXPECT_IMPL(std::string filePath, const std::string line, const std::string expectName, T1&& first, T2&& second, const bool expectResult = true)
{
	const bool equal = CONTENT_EQUAL(std::forward<T1>(first), std::forward<T2>(second));

	if(expectResult != equal) {
		const size_t fileNamePos = filePath.rfind('/');
		filePath = (fileNamePos == size_t(-1))? filePath: filePath.substr(fileNamePos);
		std::string firstString = std::to_string(first);
		std::string secondString = std::to_string(second);
		std::string errorMessage;
		errorMessage.append(filePath).append("(").append(line).append(").").append(expectName).append(": ").append(firstString).append(" and ").append(secondString);

		if(test_flag() == true) {
			std::cout << "(FAILED)" << std::endl;
		}
		test_flag() = false;

		std::cout << errorMessage << std::endl;
	};
}

#define EXPECT_EQ(first, second) EXPECT_IMPL(__FILE__, std::to_string(__LINE__), "EXPECT_EQ", first, second);
#define EXPECT_NE(first, second) EXPECT_IMPL(__FILE__, std::to_string(__LINE__), "EXPECT_NE", first, second, false);
#define EXPECT_TRUE(first) EXPECT_IMPL(__FILE__, std::to_string(__LINE__), "EXPECT_TRUE", first, true);
#define EXPECT_FALSE(first) EXPECT_IMPL(__FILE__,std::to_string(__LINE__), "EXPECT_FALSE", first, false);


template <typename TestFunction>
void RUN_TEST_IMPL(const std::string functionName, TestFunction test)
{
	try{
		test();
	} catch (std::exception& e){
		std::cerr << "A exception was called from the function " << functionName << "  with the following description: " << e.what() << std::endl;
	} catch(...) {
		std::cerr << "something else" << std::endl;
	}
}
#define RUN_TEST(function) RUN_TEST_IMPL(#function, function)

enum class TestType
{
	COMMON = 0, EXCEPTIONS = 1, STRESS = 2, ALL = -1
};

struct ITestFunctor
{
	ITestFunctor(std::string _name, std::string _path, std::string _line, TestType _type):
		name(_name),
		path(_path),
		line(_line),
		type(_type)
	{}

	std::string name;
	std::string path;
	std::string line;
	TestType type;

	std::vector<std::string> errors;
	std::string indent;

	virtual void test() = 0;
	size_t test_wrapper()
	{
		test_flag() = true;
        const size_t start = rdtsc();
		test();
        const size_t end = rdtsc();

        all_test_flag() &= test_flag();

        return end - start;
	}
};

static std::map <std::string, std::vector<std::shared_ptr<ITestFunctor>>>& get_functions()
{
	static std::map <std::string, std::vector<std::shared_ptr<ITestFunctor>>> functions;
	return functions;
}

template<typename Test>
struct TestRegister
{
	static TestRegister object;
	//template<> TestRegister<testClass##testName> TestRegister<testClass##testName>::object(#testClass, #testName);
	TestRegister(std::string testClass, std::string testName, std::string path, std::string line, TestType testType)
	{
		std::shared_ptr<ITestFunctor> test = std::make_shared<Test>(testName, path, line, testType);
		auto& functions = get_functions();
		auto it = functions.find(testClass);
		if(it == functions.end()) {
			functions.emplace(testClass, std::vector<std::shared_ptr<ITestFunctor>>{test});
		} else {
			it->second.emplace_back(test);
		}
	}
	~TestRegister()
	{}
};

template<class TestFunctor>
bool register_test(std::string testClass, std::string testName, std::string path, std::string line, TestType testType)
{
	TestRegister<TestFunctor>(std::move(testClass), std::move(testName), std::move(path), std::move(line), testType);
	return true;
}

#define TEST_FUNCTION_IMPL(FunctorName, testClass, testName, path, line, testType)\
 struct FunctorName: public ITestFunctor \
{\
	template <typename... Args> FunctorName(Args&&... args): ITestFunctor(std::forward<Args>(args)...){}\
\
	virtual void test();\
};\
static bool NAME_WITH_LINE(registerFunction,__COUNTER__) = register_test<FunctorName>(#testClass, #testName, path, std::to_string(line), testType);\
\
void FunctorName::test()\


#define TEST_FUNCTION_TYPE(testClass, testName, testType) TEST_FUNCTION_IMPL(TestFunctor##_##testClass##_##testName##_testType, testClass, testName, __FILE__, __LINE__, testType)

#define TEST_FUNCTION(testClass, testName) TEST_FUNCTION_TYPE(testClass, testName, TestType::COMMON) 

void RUN_TESTS(std::string testCategoryRegex = ".*", const std::string testNameRegex = ".*", const TestType testType = TestType::ALL)
{
	std::string lastPathFile;

	auto functions = get_functions();
	for(auto typeFunctions : functions) {
		std::string functionCategory = typeFunctions.first;
		
		std::regex regex(std::move(testCategoryRegex));
		const bool allowedCategory = std::regex_match(functionCategory, regex);
		if(!allowedCategory){
			continue;
		}

		std::cout << std::endl << "----- Function category: " << functionCategory << " -----" << std::endl;
		for(auto function : typeFunctions.second) {
			regex = std::move(testNameRegex);
			bool allowedType = (testType == TestType::ALL) || (testType == function->type);
			bool allowedName = std::regex_match(function->name, regex);
			if(!allowedType | !allowedName){
				continue;
			}
			
			const size_t fileNamePos = function->path.rfind('/');
			std::string path = fileNamePos == size_t(-1) ? function->path : function->path.substr(fileNamePos);
			if(path == lastPathFile) {
				for(auto& ch : path) {
					ch = ' ';
				}
			} else {
				lastPathFile = path;
			}

			std::cout << path << "(" << function->line << "):" << function->name << std::flush;

			const size_t cyclesElapsed = function->test_wrapper();

			if(test_flag()) {
				std::cout << "(PASSED)";
			}

			std::cout << "Cycles: " << cyclesElapsed << std::endl;
		}

	}

	if(all_test_flag()) {
		std::cout << "\n\t ALL TESTS PASSED" << std::endl;
	} else {
		std::cout << "\n\t SOME TESTS FAILED" << std::endl;
	}
}


