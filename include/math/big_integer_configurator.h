///
/// @author  Thomas Lehmann
/// @file    big_integer_configurator.h
/// @brief   the big integer impl. configurator
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
#ifndef INCLUDE_MATH_BIG_INTEGER_CONFIGURATOR_H_
#define INCLUDE_MATH_BIG_INTEGER_CONFIGURATOR_H_

#include <math/big_integer_base.h>
#include <math/big_integer_sum.h>
#include <math/big_integer_multiplication.h>

namespace math {

/// @class big_integer_configurator
/// @brief the big integer impl. configurator
class big_integer_configurator final {
    public:
        /// abbreviation for factor inside this class.
        using factory = big_integer_factory;

        /// default c'tor
        big_integer_configurator() {}

        /// registering/configuring all big_integer calculations at factory
        void configure() {
            // deleting possibly existing registrations
            factory::get().clear();

            // registering just the default SUM implementation
            factory::get().register_creator(
                int(big_integer_operation::SUM), []() {
                    return std::unique_ptr<big_integer_calculate_interface>(new big_integer_sum);
                });

            // registering just the default MULTIPLICATION implementation
            factory::get().register_creator(
                int(big_integer_operation::MULTIPLICATION), []() {
                    return std::unique_ptr<big_integer_calculate_interface>(new big_integer_multiplication);
                });
        }
};

}  // namespace math

#endif  // INCLUDE_MATH_BIG_INTEGER_CONFIGURATOR_H_
