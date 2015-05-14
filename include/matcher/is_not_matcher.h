///
/// @author  Thomas Lehmann
/// @file    is_not_matcher.h
/// @brief   matcher for negating another matcher
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
#ifndef INCLUDE_MATCHER_IS_NOT_MATCHER_H_
#define INCLUDE_MATCHER_IS_NOT_MATCHER_H_

#include <matcher/matcher.h>

namespace matcher {

/// @class is_not_matcher
/// @brief matcher for negating result of another matcher.
template <typename T>
class is_not_matcher : public matcher<T> {
    public:
        /// storing another matchere (decoration)
        is_not_matcher(const matcher<T>& value_matcher) : m_value_matcher(value_matcher) {}

        /// checking result of another matcher for given value and
        /// negating its result.
        virtual bool check(const T& expected_value) const override {
            return !m_value_matcher.check(expected_value);
        }

        /// expression of this matcher together with decorated one.
        std::string get_expression() const override {
            std::stringstream expression;
            expression << "is_not(" << m_value_matcher.get_expression() << ")";
            return expression.str();
        }

    private:
        /// given value to check agains expected value;
        const matcher<T>& m_value_matcher;
};

/// wrapper for simplifying use with assert_that statement
template <typename T>
is_not_matcher<T> is_not(const matcher<T>& matcher) {
    return is_not_matcher<T>(matcher);
}

}  // namespace matcher

#endif  // INCLUDE_MATCHER_IS_NOT_MATCHER_H_
