#include "bittricks/integers.h"
#include "gtest/gtest.h"
#include <limits>

TEST(IntegersTest, bit_size)
{
    using bittricks::bit_size;

    static_assert(bit_size<char>                == std::numeric_limits<unsigned char>::digits,      "");
    static_assert(bit_size<unsigned char>       == std::numeric_limits<unsigned char>::digits,      "");
    static_assert(bit_size<signed char>         == std::numeric_limits<unsigned char>::digits,      "");
    static_assert(bit_size<short>               == std::numeric_limits<unsigned short>::digits,     "");
    static_assert(bit_size<unsigned short>      == std::numeric_limits<unsigned short>::digits,     "");
    static_assert(bit_size<int>                 == std::numeric_limits<unsigned int>::digits,       "");
    static_assert(bit_size<unsigned int>        == std::numeric_limits<unsigned int>::digits,       "");
    static_assert(bit_size<long>                == std::numeric_limits<unsigned long>::digits,      "");
    static_assert(bit_size<unsigned long>       == std::numeric_limits<unsigned long>::digits,      "");
    static_assert(bit_size<long long>           == std::numeric_limits<unsigned long long>::digits, "");
    static_assert(bit_size<unsigned long long>  == std::numeric_limits<unsigned long long>::digits, "");
}

TEST(IntegersTest, unsigned_t)
{
    using bittricks::bit_size;
    using bittricks::unsigned_t;

    static_assert(std::is_same<unsigned_t<bit_size<char>>, unsigned char>::value,       "");

    static_assert(bit_size<unsigned_t<bit_size<char>>>       == bit_size<char>,         "");
    static_assert(bit_size<unsigned_t<bit_size<short>>>      == bit_size<short>,        "");
    static_assert(bit_size<unsigned_t<bit_size<int>>>        == bit_size<int>,          "");
    static_assert(bit_size<unsigned_t<bit_size<long>>>       == bit_size<long>,         "");
    static_assert(bit_size<unsigned_t<bit_size<long long>>>  == bit_size<long long>,    "");

    static_assert(!std::numeric_limits<unsigned_t<bit_size<char>>>::is_signed,          "");
    static_assert(!std::numeric_limits<unsigned_t<bit_size<short>>>::is_signed,         "");
    static_assert(!std::numeric_limits<unsigned_t<bit_size<int>>>::is_signed,           "");
    static_assert(!std::numeric_limits<unsigned_t<bit_size<long>>>::is_signed,          "");
    static_assert(!std::numeric_limits<unsigned_t<bit_size<long long>>>::is_signed,     "");
}
