///
/// @author  Thomas Lehmann
/// @file    sieve_interface.h
/// @brief   base class for a sieve
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
#ifndef INCLUDE_MATH_PRIME_SIEVE_INTERFACE_H_
#define INCLUDE_MATH_PRIME_SIEVE_INTERFACE_H_

namespace math {
namespace prime {

/// @class sieve_interface
/// @brief base class for sieve implementation
template <typename T>
class sieve_interface {
    public:
        /// type of container for keeping true false states
        using container_type = T;
        /// required because of derived classes only
        virtual ~sieve_interface() = default;

        /// starts sieve calculation
        virtual void calculate() noexcept = 0;
        /// @return true when given number is a prime
        virtual bool is_prime(const typename container_type::size_type number) const noexcept = 0;
};

}  // namespace prime
}  // namespace math

#endif  // INCLUDE_MATH_PRIME_SIEVE_OF_INTERFACE_H_
