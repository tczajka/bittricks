/*
 * Integer types and operations.
 *
 * Author: Tomek Czajka.
 */

#ifndef BITTRICKS_INTEGERS_H_INCLUDED
#define BITTRICKS_INTEGERS_H_INCLUDED

#include <limits>
#include <type_traits>

namespace bittricks
{

/*
 * Internals.
 */
namespace impl
{
    /*
     * The number of bits in a given integer type.
     *
     * Helper for bit_size.
     *
     * Signed types are considered to have the same number of bits as the
     * corresponding unsigned types.
     */
    template<typename T>
    constexpr int bit_size_helper()
    {
        static_assert(std::numeric_limits<T>::is_integer, "");

        using unsigned_T = std::make_unsigned_t<T>;

        static_assert(std::numeric_limits<T>::radix == 2, "");
        static_assert(std::numeric_limits<unsigned_T>::radix == 2, "");

        constexpr int bits {std::numeric_limits<unsigned_T>::digits};

        static_assert(bits == std::numeric_limits<T>::digits +
                              std::numeric_limits<T>::is_signed, "");

        return bits;
    }

    /*
     * Simple type wrapper.
     */
    template<class T>
    struct wrap_type
    { 
        using type = T;
    };

    /*
     * Helper for unsigned_t.
     *
     * Used to cause a compile error if there is no type of a given bit size.
     */
    struct undefined_unsigned_t
    {
        // 'type' not defined here.
    };

} // namespace impl

/*
 * The number of bits in a given integer type.
 *
 * Signed types are considered to have the same number of bits as the
 * corresponding unsigned types.
 *
 * In C++17, this could be an inline constexpr instead.
 */
template<typename T>
class bit_size : public std::integral_constant<int, impl::bit_size_helper<T>()> {};

/*
 * The unsigned type with the given bit_size, if one exists.
 */
template<int bits>
using unsigned_t =
    typename
    std::conditional_t<bit_size<unsigned char>::value == bits,
        impl::wrap_type<unsigned char>,
        std::conditional_t<bit_size<unsigned short>::value == bits,
            impl::wrap_type<unsigned short>,
            std::conditional_t<bit_size<unsigned>::value == bits,
                impl::wrap_type<unsigned>,
                std::conditional_t<bit_size<unsigned long>::value == bits,
                    impl::wrap_type<unsigned long>,
                    std::conditional_t<bit_size<unsigned long long>::value == bits,
                        impl::wrap_type<unsigned long long>,
                        impl::undefined_unsigned_t
                    >
                >
            >
        >
    >::type;

} // namespace bittricks

#endif
