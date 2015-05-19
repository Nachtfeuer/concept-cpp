///
/// @author  Thomas Lehmann
/// @file    has_item_matcher.h
/// @brief   matcher for checking a container to have a certain value (at least once)
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
#ifndef INCLUDE_MATCHER_HAS_ITEM_MATCHER_H_
#define INCLUDE_MATCHER_HAS_ITEM_MATCHER_H_

#include <matcher/matcher.h>
#include <algorithm>
#include <sstream>

namespace matcher {

/// @class has_item_matcher
/// @brief  matcher for checking a container to have a certain value (at least once)
template <typename T>
class has_item_matcher : public matcher<T> {
    public:
        /// storing given value required for comparison.
        has_item_matcher(const typename T::value_type& item)
            : matcher<T>()
            , m_item(item) {
        }

        /// checking container to have given item
        virtual bool check(const T& container) const override {
            auto it = std::find(container.begin(), container.end(), m_item);
            return it != container.end();
        }

        /// @return matcher expression as string
        virtual std::string get_expression() const override {
            std::stringstream expression;
            expression << "has_item(" << m_item << ")";
            return expression.str();
        }

    private:
        /// those item to be found in the given container
        const typename T::value_type m_item;
};

/// wrapper for simplifying use with assert_that statement
/// @param item is a value of given container
/// @return @ref matcher::has_item_matcher with given value.
template <typename T>
shared_matcher<T> has_item(const typename T::value_type& item) {
    return shared_matcher<T>(new has_item_matcher<T>(item));
}

}  // namespace matcher

#endif  // INCLUDE_MATCHER_HAS_ITEM_MATCHER_H_
