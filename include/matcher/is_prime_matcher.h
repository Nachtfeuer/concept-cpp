///
/// @author  Thomas Lehmann
/// @file    is_prime_matcher.h
/// @brief   matcher for checking a value to be a prime number
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
#ifndef INCLUDE_MATCHER_IS_PRIME_MATCHER_H_
#define INCLUDE_MATCHER_IS_PRIME_MATCHER_H_

#include <matcher/matcher.h>
#include <math/prime/is_prime.h>

namespace matcher {

/// @class is_prime_matcher
/// @brief matcher for checking a value to be a prime number
template <typename T>
class is_prime_matcher : public matcher<T> {
    public:
        /// default c'tor
        is_prime_matcher()
            : matcher<T>() {}

        /// @return true when value is a prime.
        /// @see @ref math::prime::is_prime
        virtual bool check(const T& expected_value) const override {
            return math::prime::is_prime(expected_value);
        }

        /// @return matcher expression as string
        virtual std::string get_expression() const override {
            return "is_prime()";
        }
};

/// wrapper for simplifying use with assert_that statement
template <typename T>
shared_matcher<T> is_prime() {
    return shared_matcher<T>(new is_prime_matcher<T>);
}

}  // namespace matcher

#endif  // INCLUDE_MATCHER_IS_PRIME_MATCHER_H_
