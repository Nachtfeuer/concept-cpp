///
/// @author  Thomas Lehmann
/// @file    is_equal_matcher.h
/// @brief   matcher for checking on to be equal.
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
#ifndef INCLUDE_UNITTEST_IS_EQUAL_MATCHER_H_
#define INCLUDE_UNITTEST_IS_EQUAL_MATCHER_H_

#include <unittest/matcher.h>

namespace unittest {

/// @class is_equal_matcher
/// @brief matcher for checking on to be equal.
template <typename T>
class is_equal_matcher : public matcher<T> {
    public:
        /// storing given value required for comparison.
        is_equal_matcher(const T& given_value) : m_given_value(given_value) {}

        /// checking on to be equal
        virtual bool check(const T& expected_value) const override {
            return expected_value == m_given_value;
        }

        /// @return matcher expression as string
        std::string get_expression() const override {
            std::stringstream expression;
            expression << "is_equal(" << m_given_value << ")";
            return expression.str();
        }

    private:
        /// given value to check agains expected value;
        const T& m_given_value;
};

/// wrapper for simplifying use with assert_that statement
template <typename T>
is_equal_matcher<T> is_equal(const T& given_value) {
    return is_equal_matcher<T>(given_value);
}

}  // namespace unittest

#endif  // INCLUDE_UNITTEST_IS_EQUAL_MATCHER_H_
