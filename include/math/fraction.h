///
/// @author  Thomas Lehmann
/// @file    fraction.h
/// @brief   math fraction
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
#ifndef INCLUDE_MATH_FRACTION_H_
#define INCLUDE_MATH_FRACTION_H_

#include <iostream>

namespace math {

/// @class fraction
/// @brief  math fraction.
/// @note read here: http://en.wikipedia.org/wiki/Fraction_%28mathematics%29
template <typename T>
class fraction final {
    public:
        /// init c'tor
        constexpr fraction(const T numerator, const T denominator) noexcept
            : m_numerator(numerator), m_denominator(denominator) {
        }

        /// value above the line (or before the slash)
        /// @return readonly access to denominator
        constexpr T get_numerator() const noexcept {
            return m_numerator;
        }

        /// value below the line (or after the slash)
        /// @return readonly access to denominator
        constexpr T get_denominator() const noexcept {
            return m_denominator;
        }

        /// Does calculate the sum of two fractions like \f$\frac{1}{2}+\frac{2}{3}=\frac{7}{6}\f$
        /// @return sum of two fractions
        constexpr friend fraction operator + (const fraction& lhs, const fraction& rhs) noexcept {
            return fraction(lhs.get_numerator() * rhs.get_denominator() +
                            lhs.get_denominator() * rhs.get_numerator(),
                            lhs.get_denominator() * rhs.get_denominator());
        }

        /// Does calculate the sum of two fractions like \f$\frac{1}{2}-\frac{2}{3}=\frac{-1}{6}\f$
        /// @return difference of two fractions
        constexpr friend fraction operator - (const fraction& lhs, const fraction& rhs) noexcept {
            return fraction(lhs.get_numerator() * rhs.get_denominator() -
                            lhs.get_denominator() * rhs.get_numerator(),
                            lhs.get_denominator() * rhs.get_denominator());
        }

        /// Does calculate the sum of two fractions like \f$\frac{1}{2}*\frac{2}{3}=\frac{2}{6}\f$
        /// @return product of two fractions
        constexpr friend fraction operator * (const fraction& lhs, const fraction& rhs) noexcept {
            return fraction(lhs.get_numerator() * rhs.get_numerator(),
                            lhs.get_denominator() * rhs.get_denominator());
        }

        /// Does calculate the sum of two fractions like \f$\frac{1}{2}/\frac{2}{3}=\frac{3}{4}\f$
        /// @return division of two fractions
        constexpr friend fraction operator / (const fraction& lhs, const fraction& rhs) noexcept {
            return fraction(lhs.get_numerator() * rhs.get_denominator(),
                            lhs.get_denominator() * rhs.get_numerator());
        }

        /// compares two fractions on to be equal
        friend bool operator == (const fraction& lhs, const fraction& rhs) noexcept {
            if (lhs.get_denominator() == rhs.get_denominator()) {
                return lhs.get_numerator() == rhs.get_numerator();
            }

            return lhs.get_numerator() * rhs.get_denominator() ==
                   rhs.get_numerator() * lhs.get_denominator();
        }

        /// dumping fraction to stream
        friend std::ostream& operator << (std::ostream& stream, const fraction& f) {
            stream << "fraction(" << f.get_numerator() << ", " << f.get_denominator() << ")";
            return stream;
        }

    private:
        /// value above the line (or before the slash)
        T m_numerator;
        /// value below the line (or after the slash)
        T m_denominator;
};

}  // namespace math

#endif  // INCLUDE_MATH_FRACTION_H_
