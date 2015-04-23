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
#ifndef INCLUDE_ASSERT_H_
#define INCLUDE_ASSERT_H_

#include <unittest/matcher.h>

#include <string.h>
#include <sstream>
#include <iostream>
#include <exception>

namespace unittest {

/// @class assertion
/// @brief exception representing a failed test
class assertion : public std::exception {
    public:
        /// providing assertion message
        assertion(const std::string& message)
            : m_message(message) {}

        /// @return assertion message
        virtual const char* what() const noexcept override {
            return m_message.c_str();
        }

    private:
        /// message explaining the assertion
        const std::string m_message;
};

template <typename T>
void assert_that(const T& expected_value, const matcher<T>& value_matcher) {
    if (!value_matcher.check(expected_value)) {
        std::stringstream message;
        message << " ...... assertion: " << expected_value
                << " does not match "
                << value_matcher.get_expression();
        throw assertion(message.str());
    }
}
    
}  // namespace unittest

#endif  // INCLUDE_ASSERT_H_
