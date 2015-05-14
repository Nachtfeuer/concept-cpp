///
/// @author  Thomas Lehmann
/// @file    matcher.h
/// @brief   matcher base class and functions.
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
#ifndef INCLUDE_MATCHER_MATCHER_H_
#define INCLUDE_MATCHER_MATCHER_H_

#include <string>

namespace matcher {

/// @class matcher
/// @brief matcher base class and functions.
template <typename T>
class matcher {
    public:
        /// @return true when expected value does match
        virtual bool check(const T& expected_value) const = 0;
        /// @return chain of matchers as readable string expression
        virtual std::string get_expression() const = 0;
};

}  // namespace matcher

#endif  // INCLUDE_MATCHER_MATCHER_H_
