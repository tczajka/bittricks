#include "bittricks/integers.h"
#include "gtest/gtest.h"
#include <limits>

TEST(IntegersTest, bit_size)
{
    using bittricks::bit_size;

    static_assert(bit_size<char>::value                 == std::numeric_limits<unsigned char>::digits,      "");
    static_assert(bit_size<unsigned char>::value        == std::numeric_limits<unsigned char>::digits,      "");
    static_assert(bit_size<signed char>::value          == std::numeric_limits<unsigned char>::digits,      "");
    static_assert(bit_size<short>::value                == std::numeric_limits<unsigned short>::digits,     "");
    static_assert(bit_size<unsigned short>::value       == std::numeric_limits<unsigned short>::digits,     "");
    static_assert(bit_size<int>::value                  == std::numeric_limits<unsigned int>::digits,       "");
    static_assert(bit_size<unsigned int>::value         == std::numeric_limits<unsigned int>::digits,       "");
    static_assert(bit_size<long>::value                 == std::numeric_limits<unsigned long>::digits,      "");
    static_assert(bit_size<unsigned long>::value        == std::numeric_limits<unsigned long>::digits,      "");
    static_assert(bit_size<long long>::value            == std::numeric_limits<unsigned long long>::digits, "");
    static_assert(bit_size<unsigned long long>::value   == std::numeric_limits<unsigned long long>::digits, "");
}

TEST(IntegersTest, unsigned_t)
{
    using bittricks::bit_size;
    using bittricks::unsigned_t;

    static_assert(std::is_same<unsigned_t<bit_size<char>::value>, unsigned char>::value,       "");

    static_assert(bit_size<unsigned_t<bit_size<char>::value>>::value        == bit_size<char>::value,      "");
    static_assert(bit_size<unsigned_t<bit_size<short>::value>>::value       == bit_size<short>::value,     "");
    static_assert(bit_size<unsigned_t<bit_size<int>::value>>::value         == bit_size<int>::value,       "");
    static_assert(bit_size<unsigned_t<bit_size<long>::value>>::value        == bit_size<long>::value,      "");
    static_assert(bit_size<unsigned_t<bit_size<long long>::value>>::value   == bit_size<long long>::value, "");

    static_assert(!std::numeric_limits<unsigned_t<bit_size<char>::value>>::is_signed,      "");
    static_assert(!std::numeric_limits<unsigned_t<bit_size<short>::value>>::is_signed,     "");
    static_assert(!std::numeric_limits<unsigned_t<bit_size<int>::value>>::is_signed,       "");
    static_assert(!std::numeric_limits<unsigned_t<bit_size<long>::value>>::is_signed,      "");
    static_assert(!std::numeric_limits<unsigned_t<bit_size<long long>::value>>::is_signed, "");
}
