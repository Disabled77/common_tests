#pragma once
#include <x86intrin.h>
#include <stdexcept>
#include <random>
#include <array>
#include <tgmath.h>

namespace common {

#define MEASURE_CYCLES(action)\
     [&]() -> unsigned long long\
     { \
        auto start = rte_rdtsc_precise();\
        action; \
        return rte_rdtsc_precise() - start;\
     }()



template <typename T>
constexpr bool is_power_2(T number) {
    static_assert(std::numeric_limits<T>::is_integer && (!std::numeric_limits<T>::is_signed), "I must be unsigned integer");
    return ((number & (number - 1)) == 0) && (number != 0);
}

template <typename T, std::size_t size>
std::array<T, size> create_random_array()
{
    std::array<T, size> result;
    std::random_device random_device;

    for (std::size_t i = 0; i < size; ++i)
    {
        result.at(i) = static_cast<T>(random_device());
    }

    return std::move(result);
}

template <typename T>
static constexpr bool is_integer(T value)
{
    return value == std::floor(value);
}

template <typename T>
void unused(T&&)
{}

template <typename Type>
Type get_max_value(Type) {
    return std::numeric_limits<Type>::max();
}

template <unsigned long long first, unsigned long long second>
struct Max {
    static constexpr unsigned long long value = first > second ? first : second;
};

#define SIZE_C_(x) \
    static_cast<std::size_t>(x ## ULL)

#define SIZE_C(x) \
    SIZE_C_(x)

#define TO_SIZE(x)\
    static_cast<std::size_t>(x)

#define TO_U32(x)\
    static_cast<std::uint32_t>(x)

#define TO_UNSIGNED(x)\
    static_cast<unsigned int>(x)

template <typename T>
void assert_is_power_of_two(T number){
    if(!is_power_2(number)){
        throw std::logic_error{"the number must be a power of two"};
    }
}

#ifdef DEBUG
inline void assert_impl(bool condition, const char* conditionStr, const char* fileStr, int line, const char* message)
{
    if (!condition) {
    rte_exit(-1, "DEBUG_ASSERT(%s) failed at %s:%i with message: %s\n", conditionStr, fileStr, line, message);
    }
}
#define DEBUG_ASSERT(condition, message) \
common::assert_impl((condition), #condition, __FILE__, __LINE__, (message))
#else
#define DEBUG_ASSERT(condition, message) \
    {}
#endif

#ifdef DEBUG
#define INLINE
#else
#define INLINE __attribute__ ((__always_inline__))
#endif

} // namespace common



