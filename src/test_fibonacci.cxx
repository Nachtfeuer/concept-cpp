///
/// @author  Thomas Lehmann
/// @file    test_fibonacci.cxx
/// @brief   testing of @ref math::fibonacci functions.
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
#include <unittest/unittest.h>
#include <math/fibonacci.h>

#include <vector>
#include <cstdint>

using namespace unittest;
using container_type = std::vector<uint32_t>;

/// testing of class @ref math::fibonacci
describe_suite("testing math::fibonacci", [](){
    describe_test("testing @ref math::fibonacci::by_index function", []() {
        const container_type fibonacci_sequence
            = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181};

        for (container_type::value_type index = 0; index < fibonacci_sequence.size(); ++index) {
            assert_that(fibonacci_sequence[index],
                        is_equal(math::fibonacci::by_index(index)));
        }
    });
});

