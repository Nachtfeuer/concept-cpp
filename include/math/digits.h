///
/// @author  Thomas Lehmann
/// @file    digits.h
/// @brief   digit algorithms
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
#ifndef INCLUDE_MATH_DIGITS_H_
#define INCLUDE_MATH_DIGITS_H_

#include <set>
#include <cstdint>

namespace math {

/// @struct digits
template <typename T>
struct digits final {
    /// @return sum of digits
    inline static T sum(const T number) noexcept {
        auto result = T(0);
        for (auto n = number; n != 0; n /= 10) {
            result += n % 10;
        }
        return result;
    }

    /// @return number of digits
    inline static T count(const T number) noexcept {
        if (0 == number) {
            return 1;
        }

        auto result = T(0);
        for (auto n = number; n != 0; n /= 10) {
            ++result;
        }
        return result;
    }

    /// Checks that each digit appears once only
    /// @return true when given number is pandigital
    /// @see http://en.wikipedia.org/wiki/Pandigital_number
    inline static bool is_pandigital(const T number) noexcept {
        std::set<unsigned char> digits;
        for (auto n = number; n != 0; n /= 10) {
            digits.insert(n % 10);
        }

        return count(number) == digits.size();
    }

    /// Check that given number is a palindrom like: 161, 2332, ..
    /// @return true when given number is a palindrom
    /// @see http://en.wikipedia.org/wiki/Palindromic_number
    inline static bool is_palindrome(const T number) noexcept {
        std::vector<unsigned char> digits;
        for (auto n = number; n != 0; n /= 10) {
            digits.push_back(n % 10);
        }

        const auto max_idx = static_cast<uint64_t>(digits.size() - 1);
        for (auto left = static_cast<uint64_t>(0), right = max_idx; left < right; ++left, --right) {
            if (digits[left] != digits[right]) {
                return false;
            }
        }

        return true;
    }

    /// @Generating reversed integer like: 12345 => 54321.
    /// @param number the integer to get reversed
    /// @return reverse integer
    inline static T reverse(const T number) noexcept {
        auto result = T(0);
        for (auto n = number; n != 0; n /= 10) {
            result = result * 10 + n % 10;
        }
        return result;
    }

    /// instantiation is not wanted
    digits() = delete;
};

}  // namespace math

#endif  // INCLUDE_MATH_DIGITS_H_
