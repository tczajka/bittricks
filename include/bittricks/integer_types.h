/*
 * Unsigned types and operations.
 *
 * Author: Tomek Czajka.
 */

#ifndef BITTRICKS_UNSIGNED_T_H_INCLUDED
#define BITTRICKS_UNSIGNED_T_H_INCLUDED

#include <limits>
#include <type_traits>

namespace bittricks
{

namespace impl
{
    /*
     * bit_size as a function
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

    template<class T>
    struct wrap_type
    { 
        using type = T;
    };

    /*
     * Indicated that unsigned_t can't be formed at compile time.
     */
    struct undefined_unsigned_t
    {
    };

} // namespace impl

/*
 * The number of bits in a given integer type.
 *
 * Signed types are considered to have the same number of bits as the
 * corresponding unsigned types.
 */
template<typename T>
constexpr int bit_size {impl::bit_size_helper<T>()};

/*
 * The unsigned type with the given bit_size, if one exists.
 */
template<int bits>
using unsigned_t =
    typename
    std::conditional_t<bit_size<unsigned char> == bits,
        impl::wrap_type<unsigned char>,
        std::conditional_t<bit_size<unsigned short> == bits,
            impl::wrap_type<unsigned short>,
            std::conditional_t<bit_size<unsigned> == bits,
                impl::wrap_type<unsigned>,
                std::conditional_t<bit_size<unsigned long> == bits,
                    impl::wrap_type<unsigned long>,
                    std::conditional_t<bit_size<unsigned long long> == bits,
                        impl::wrap_type<unsigned long long>,
                        impl::undefined_unsigned_t
                    >
                >
            >
        >
    >::type;

} // namespace bittricks

#endif
