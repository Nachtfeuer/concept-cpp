///
/// @author  Thomas Lehmann
/// @file    is_range_matcher.h
/// @brief   matcher for checking a value to be in given range
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
#ifndef INCLUDE_MATCHER_IS_RANGE_MATCHER_H_
#define INCLUDE_MATCHER_IS_RANGE_MATCHER_H_

#include <matcher/matcher.h>

namespace matcher {

/// @class is_range_matcher
/// @brief matcher for checking to be in given range
template <typename T>
class is_range_matcher : public matcher<T> {
    public:
        /// storing given value required for comparison.
        is_range_matcher(const T& from_value, const T& to_value)
            : m_from_value(from_value), m_to_value(to_value) {
        }

        /// checking on to be equal
        virtual bool check(const T& expected_value) const override {
            return expected_value >= m_from_value && expected_value <= m_to_value;
        }

        /// @return matcher expression as string
        std::string get_expression() const override {
            std::stringstream expression;
            expression << "is_range(" << m_from_value << ", " << m_to_value << ")";
            return expression.str();
        }

    private:
        /// given value to be greater or equal than this value
        const T m_from_value;
        /// given value to be less or equal than this value
        const T m_to_value;
};

/// wrapper for simplifying use with assert_that statement
template <typename T>
shared_matcher<T> is_range(const T& from_value, const T& to_value) {
    return shared_matcher<T>(new is_range_matcher<T>(from_value, to_value));
}

}  // namespace matcher

#endif  // INCLUDE_MATCHER_IS_RANGE_MATCHER_H_
