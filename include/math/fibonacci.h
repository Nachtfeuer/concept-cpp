///
/// @author  Thomas Lehmann
/// @file    fibonacci.h
/// @brief   math fibonacci functions.
/// @note    read here: http://en.wikipedia.org/wiki/Fibonacci_number
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
#ifndef INCLUDE_MATH_FIBONACCI_H_
#define INCLUDE_MATH_FIBONACCI_H_

#include <cstdint>

namespace math {

/// @class fibonacci
/// @brief tool class for static fibonacci functions.
class fibonacci final {
    public:
        /// @param zero based index in the fibonacci sequence.
        /// @return fibonacci value at given index in its sequence.
        ///
        /// @code
        /// std::vector<uint32_t> fibonacci_sequence = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
        /// for (auto index = 0; index < fibonacci_sequence.size(); ++index) {
        ///     assert_that(fibonacci_sequence[index], is_equal(math::fibonacci::by_index(index)));
        /// }
        /// @endcode
        inline static uint32_t by_index(const uint32_t index) noexcept {
            if (0 == index) {
                return 0;
            }

            if (index <= 2) {
                return 1;
            }

           auto last_before_last = static_cast<uint32_t>(1);
           auto last = static_cast<uint32_t>(1);

           auto current_index = index - 2;
           while (current_index-- > 0) {
               const auto temp = last + last_before_last;
               last_before_last = last;
               last = temp;
           }

           return last;
        }

    private:
        /// disable c'tor
        fibonacci() = delete;
};

}  // namespace math

#endif  // INCLUDE_MATH_FIBONACCI_H_
