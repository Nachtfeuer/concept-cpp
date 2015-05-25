///
/// @author  Thomas Lehmann
/// @file    is_prime.h
/// @brief   is prime checker
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
#ifndef INCLUDE_MATH_PRIME_IS_PRIME_H_
#define INCLUDE_MATH_PRIME_IS_PRIME_H_

#include <cmath>

namespace math {
namespace prime {

/// @param value value to be checked
/// @return true when given value is a prime
/// @note for really big numbers or for creating a list of primes
///       consider to use a sieve algorithms. This algorithm is
///       rather slow.
template <typename T>
inline bool is_prime(const T& value) noexcept {
    if (value < 2) {
        return false;
    }

    if (value % 2 == 0) {
        return value == 2;
    }

    const auto limit = static_cast<T>(sqrt(value));
    for (T divisor = 3; divisor <= limit; divisor += 2) {
        if (value % divisor == 0) {
            return false;
        }
    }

    return true;
}

}  // namespace prime
}  // namespace math

#endif  // INCLUDE_MATH_PRIME_IS_PRIME_H_
