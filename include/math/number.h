///
/// @author  Thomas Lehmann
/// @file    number.h
/// @brief   special number functions
///
/// Copyright (c) 2015 Thomas Lehmann
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
/// documentation files (the "Software"), to deal in the Software without restriction, including without limitation
/// the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
/// and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies
/// or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
/// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
/// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY,
/// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#ifndef INCLUDE_MATH_NUMBER_H_
#define INCLUDE_MATH_NUMBER_H_

#include <math/factorization.h>
#include <math/digits.h>
#include <algorithm>
#include <numeric>
#include <cmath>

namespace math {

/// @struct number
template <typename T>
struct number final {
    /// Checks a number to be perfect; 6 is the first one (1+2+3=6 which is equal to 6).
    /// @return true when the sum of the divisors of the given number is equal to the number
    /// @note that function is very performance intensive and the numbers grow very fast!
    /// @see http://en.wikipedia.org/wiki/Perfect_number
    /// @see here: oeis.org/A000396
    inline static bool is_perfect(const T number) noexcept {
        typename factorization<T>::container_type divisors;
        factorization<T>::probe(number, divisors);
        return (std::accumulate(divisors.begin(), divisors.end(), 0) - number) == number;
    }

    /// Checks a number to be abundant; 12 is the first one (1+2+3+4+6=16 which is greater than 12).
    /// @return true when the sum of the divisors of the given number is greater as the number
    /// @see http://en.wikipedia.org/wiki/Abundant_number
    inline static bool is_abundant(const T number) noexcept {
        typename factorization<T>::container_type divisors;
        factorization<T>::probe(number, divisors);
        return (std::accumulate(divisors.begin(), divisors.end(), 0) - number) > number;
    }

    /// Checks a number to be square like 9 (which is - of course - 3*3).
    /// @return true when given number is a square
    inline static bool is_square(const T number) noexcept {
        const auto value = sqrt(number);
        return value == static_cast<T>(value);
    }

    /// <i>n</i>th triangle number can be calculated by this formula:
    /// \f$t_n = \frac{n \cdot (n + 1)}{2}\f$
    /// @return nth triangle nummber (1st:1, 2nd: 3, 3rd: 6, 4th: 10, ...)
    /// @see http://en.wikipedia.org/wiki/Triangular_number
    /// @note for nth >= 1
    inline static T triangle(const T nth) noexcept {
        return (nth * (nth + 1)) / 2;
    }

    /// Testing for being a triangle number can be done by verifying that
    /// the result of following formula is a square number: \f$8 \cdot n + 1\f$
    /// @return true when given number is a triangle number
    /// @see http://en.wikipedia.org/wiki/Triangular_number
    inline static bool is_triangle(const T number) noexcept {
        return is_square(8 * number + 1);
    }

    /// <i>n</i>th pentagonal number can be calculated by this formula:
    /// \f$p_n = \frac{n \cdot (3 \cdot n - 1)}{2}\f$
    /// @return nth pentagonal nummber (1st:1, 2nd: 5, 3rd: 12, 4th: 22, ...)
    /// @see http://en.wikipedia.org/wiki/Pentagonal_number
    /// @note for nth >= 1
    inline static T pentagonal(const T nth) noexcept {
        return (nth * (3 * nth - 1)) / 2;
    }

    /// Testing for being a pentagonal number can be calculated by this formula:
    /// \f$n = \frac{\sqrt{24 \cdot x + 1} + 1}{6}\f$
    /// @return true when given number is a pentagonal number
    /// @see http://en.wikipedia.org/wiki/Triangular_number
    inline static bool is_pentagonal(const T number) noexcept {
        const auto value = (sqrt(24 * number + 1) + 1) / 6.0;
        return value > 0 && value == static_cast<T>(value);
    }

    /// <i>n</i>th hexagonal number can be calculated by this formula: \f$h_n = n \cdot (2 \cdot n - 1)\f$
    /// @return nth hexagonal number (1st: 1, 2nd: 6, 3rd: 15, 4th: 28, ...)
    /// @see http://en.wikipedia.org/wiki/Hexagonal_number
    /// @note for nth >= 1
    inline static T hexagonal(const T nth) noexcept {
        return nth * (2 * nth - 1);
    }

    /// Testing for being a hexagonal number can be calculated by this formula:
    /// \f$n = \frac{\sqrt{8 \cdot x + 1} + 1}{4}\f$
    /// When the result is an integer value then it is a hexagonal number.
    ///
    /// @return true when given number is a hexagonal number
    /// @see http://en.wikipedia.org/wiki/Hexagonal_number
    inline static bool is_hexagonal(const T number) noexcept {
        const auto value = (sqrt(8 * number + 1) + 1) / 4.0;
        return value == static_cast<T>(value);
    }

    /// @copydoc @ref math::digits::is_pandigital
    inline static bool is_pandigital(const T number) noexcept {
        return digits<T>::is_pandigital(number);
    }

    /// @copydoc @ref math::digits::is_palindrom
    inline static bool is_palindrome(const T number) noexcept {
        return digits<T>::is_palindrome(number);
    }

    /// @copydoc @ref math::digits::reverse
    inline static T reverse(const T number) noexcept {
        return digits<T>::reverse(number);
    }
};

}  // namespace math

#endif  // INCLUDE_MATH_NUMBER_H_
