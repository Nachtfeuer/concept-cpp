///
/// @author  Thomas Lehmann
/// @file    big_integer_base.h
/// @brief   data structure, definitions and base classes / interfaces
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
#ifndef INCLUDE_MATH_BIG_INTEGER_BASE_H_
#define INCLUDE_MATH_BIG_INTEGER_BASE_H_

#include <pattern/factory.h>
#include <vector>

namespace math {

/// smallest possible type to represent one digit
/// without extra work to be able to work with it
/// in calculations.
using digit_type = unsigned char;

/// container with digits
using digits_type = std::vector<digit_type>;

/// supported operations by big integer class
/// @note SUM at the moment only
enum class big_integer_operation : int {
    SUM, DIFFERENCE, MULTIPLICATION, DIVISION
};

/// base class for a generic interface to allow clean interface
/// for different implementation, like sum, difference and multiplication
class big_integer_calculate_interface {
    public:
        /// default d'tor.
        virtual ~big_integer_calculate_interface() = default;
        /// required to be implemented by derived class: destination = destination + source
        virtual void calculate(digits_type& destination,
                               const digits_type& source) const noexcept = 0;
};

/// factory which allows defining own implementation for big integer operations
using big_integer_factory = pattern::factory<int, big_integer_calculate_interface>;

}  // namespace math

#endif   // INCLUDE_MATH_BIG_INTEGER_BASE_H_
