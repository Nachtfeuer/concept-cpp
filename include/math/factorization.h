///
/// @author  Thomas Lehmann
/// @file    factorizatioon.h
/// @brief   factorization algorithms
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
#ifndef INCLUDE_MATH_FACTORIZATION_H_
#define INCLUDE_MATH_FACTORIZATION_H_

#include <vector>

namespace math {

/// @struct factorization
template <typename T>
struct factorization final {
    /// type of container of values
    using container_type = std::vector<T>;

    /// The divisors for 10 are 1, 2, 5 and 10.
    /// @param value [in] value for which to find all factors
    /// @param divisors [out] found divisors
    inline static void probe(const T value, container_type& divisors) noexcept {
        const auto limit = value / 2;

        divisors.clear();
        divisors.push_back(1);

        for (auto divisor = 2; divisor <= limit; ++divisor) {
            if (value % divisor == 0) {
                divisors.push_back(divisor);
            }
        }

        if (1 != value) {
            divisors.push_back(value);
        }
    }

    /// we don't want to have instantiation
    factorization() = delete;
};

}  // namespace math

#endif  // INCLUDE_MATH_FACTORIZATION_H_
