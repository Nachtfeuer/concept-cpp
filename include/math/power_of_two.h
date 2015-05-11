///
/// @author  Thomas Lehmann
/// @file    power_of_two.h
/// @brief   math 2^x function.
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
#ifndef INCLUDE_MATH_POWER_OF_TWO_H_
#define INCLUDE_MATH_POWER_OF_TWO_H_

#include <iostream>
#include <vector>
#include <cstdint>

namespace math {

/// @class power_of_two
/// @brief math 2^x function.
class power_of_two final {
    public:
        /// type representing smallest type for one digit
        using digit = unsigned char;
        /// type for container of digits
        using container = std::vector<digit>;

        /// initializing defaults
        power_of_two()
            : m_digits() {}

        /// does the calculation of 2^x.
        void calculate(uint32_t exponent) noexcept {
            reset();
            while (exponent > 0) {
                auto index = static_cast<uint32_t>(0);
                auto rest = static_cast<digit>(0);

                while (index < m_digits.size()) {
                    auto value = m_digits[index] * 2 + rest;
                    m_digits[index] = value % 10;
                    rest = value / 10;
                    ++index;
                }

                if (rest > 0) {
                    m_digits.push_back(rest);
                }
                --exponent;
            }
        }

        /// @param stream is stream to write result to
        /// @param pot is the object with current result
        /// @return stream to continue write operations
        friend std::ostream& operator << (std::ostream& stream, const power_of_two& pot) {
            for (int32_t index = pot.m_digits.size() - 1; index >= 0; --index) {
                stream << static_cast<uint32_t>(pot.m_digits[index]);
            }
            return stream;
        }

    private:
        /// does reset the previous result
        void reset() noexcept {
            m_digits.clear();
            m_digits.push_back(1);
        }

        /// all calculated digits
        container m_digits;
};

}  // namespace math

#endif  // INCLUDE_MATH_POWER_OF_TWO_H_
