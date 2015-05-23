///
/// @author  Thomas Lehmann
/// @file    big_integer_sum.h
/// @brief   calculating sum of two big integer data
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
#ifndef INCLUDE_MATH_BIG_INTEGER_SUM_H_
#define INCLUDE_MATH_BIG_INTEGER_SUM_H_

#include <math/big_integer_base.h>

namespace math {

/// @class big_integer_sum
/// @brief calculating sum of two big integer data
class big_integer_sum final : public big_integer_calculate_interface {
    public:
        /// @param destination first term of sum and also the result destination
        /// @param sources second term of sum
        virtual void calculate(digits_type& destination,
                               const digits_type& source) const noexcept {
            auto digit_a = destination.begin();
            auto rest = static_cast<digit_type>(0);
            for (const auto& digit_b: source) {
                if (digit_a == destination.end()) {
                    const auto value = digit_b + rest;
                    destination.push_back(value % 10);
                    rest = value / 10;
                    // required since we have modified the "memory" of the container
                    digit_a = destination.end();
                } else {
                    const auto value = *digit_a + digit_b + rest;
                    *digit_a = value % 10;
                    rest = value / 10;
                    ++digit_a;
                }
            }

            if (rest > 0) {
                destination.push_back(rest);
            }
        }
};

}  // namespace math

#endif  // INCLUDE_MATH_BIG_INTEGER_SUM_H_
