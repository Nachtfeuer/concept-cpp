///
/// @author  Thomas Lehmann
/// @file    sieve_of_eratosthenes_optimized.h
/// @brief   prime sieve implementation
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
#ifndef INCLUDE_MATH_PRIME_SIEVE_OF_ERATOSTENES_OPTIMIZED_H_
#define INCLUDE_MATH_PRIME_SIEVE_OF_ERATOSTENES_OPTIMIZED_H_

#include <math/prime/sieve_interface.h>
#include <stdexcept>
#include <cmath>

namespace math {
namespace prime {

/// @class sieve_of_eratosthenes_optimized
/// @brief prime sieve implementation
///
/// Idea is to strikeout all multiples of a found prime.
/// @see http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
///
/// @note does NOT store even values (less memory consumption)
/// @note the algorithm is also not sensible enough to avoid
///       striking out a none prime more than once.
template <typename T>
class sieve_of_eratosthenes_optimized final : public sieve_interface<T> {
    public:
        /// type of container for keeping true false states
        using container_type = typename sieve_interface<T>::container_type;
        /// type for the numbers in the calculation
        using value_type = uint64_t;

        /// init c'tor which defines the maximum number that can
        /// be checked to be a prime (or not)
        sieve_of_eratosthenes_optimized(value_type max_n)
            : sieve_interface<T>(), m_max_n(max_n), m_is_prime(max_n/2, true) {
                m_is_prime[0] = false;
                m_is_prime[1] = true;
            }

        /// calculating the prime states striking out all multiples of a
        /// found prime.
        void calculate() noexcept override {
            auto max_limit = static_cast<value_type>(m_max_n);
            auto min_limit = static_cast<value_type>(sqrt(m_max_n));

            for (value_type i = 3; i <= min_limit; i += 2) {
                if (m_is_prime[i/2]) {
                    const auto offset = 2*i;
                    for (value_type j = i*i; j < max_limit; j += offset) {
                        m_is_prime[j/2] = false;
                    }
                }
            }
        }

        /// @return true when given number is a prime
        bool is_prime(const typename container_type::size_type number) const noexcept override {
            if (number % 2 == 0) {
                return 2 == number;
            }

            try {
                return m_is_prime[number / 2];
            } catch (const std::exception& e) {
                return false;
            }
        }

    private:
        value_type m_max_n;
        /// container for keeping true/false states
        container_type m_is_prime;
};

}  // namespace prime
}  // namespace math

#endif  // INCLUDE_MATH_PRIME_SIEVE_OF_ERATOSTENES_OPTIMIZED_H_
