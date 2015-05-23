///
/// @author  Thomas Lehmann
/// @file    big_integer.h
/// @brief   the big integer class
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
#ifndef INCLUDE_MATH_BIG_INTEGER_H_
#define INCLUDE_MATH_BIG_INTEGER_H_

#include <math/big_integer_base.h>
#include <pattern/factory.h>

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <cstdint>

namespace math {

/// @class big_integer
/// @brief being able to calculate bigger numbers than the standard types.
class big_integer {
    public:
        /// factory which allows defining own implementation for big integer operations
        using factory = pattern::factory<int, big_integer_calculate_interface>;

        /// default c'tor
        big_integer()
            : m_digits() {
        }

        /// init c'tor
        big_integer(const digits_type& digits)
            : m_digits(digits) {
        }

        /// adding another big integer to given value
        /// @return this to allow to continue with further operations.
        /// @note for the moment we create an implementation each call
        ///       which will be changed.
        const big_integer& operator += (const big_integer& rhs) noexcept {
            auto operation = factory::get().create_instance(int(big_integer_operation::SUM));
            if (!operation) {
                throw std::runtime_error("Missing SUM implementation!");
            }

            operation->calculate(m_digits, rhs.m_digits);
            return *this;
        }

        /// @return sum of two big integer
        friend big_integer operator + (const big_integer& lhs, const big_integer& rhs) {
            return big_integer(lhs) += rhs;
        }

        /// dumping big integer content to stream
        friend std::ostream& operator << (std::ostream& stream, const big_integer& bi) {
            const auto itEnd = bi.m_digits.rend();
            stream << "big_integer(";
            for (auto it = bi.m_digits.rbegin(); it != itEnd; ++it) {
                stream << static_cast<uint32_t>(*it);
            }
            stream << ")";
            return stream;
        }

        /// providing big_integer "value" as string
        std::string to_string() const noexcept {
            const auto itEnd = m_digits.rend();
            std::stringstream stream;
            for (auto it = m_digits.rbegin(); it != itEnd; ++it) {
                stream << static_cast<uint32_t>(*it);
            }
            return stream.str();
        }

        /// @return number of digits in the integer
        digits_type::size_type size() const noexcept {
            return m_digits.size();
        }

        /// @return true when there is no digit defined
        bool empty() const noexcept {
            return m_digits.empty();
        }

    private:
        /// stored digits
        digits_type m_digits;
};

}  // namespace math


#endif   // INCLUDE_MATH_BIG_INTEGER_H_
