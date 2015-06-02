///
/// @author  Thomas Lehmann
/// @file    test_big_integer_multiplication.cxx
/// @brief   testing of @ref math::big_integer_multiplication
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
#include <math/big_integer_multiplication.h>

using namespace unittest;
using namespace matcher;

/// testing of class @ref math::big_integer_multiplication
describe_suite("testing math::big_integer_multiplication", [](){
    describe_test("testing same number length", []() {
        math::digits_type value_a = {2, 3};              // 32
        const math::digits_type value_b = {2, 3};        // 32
        const math::digits_type expected = {4, 2, 0, 1}; // 1024

        math::big_integer_multiplication bimult;
        bimult.calculate(value_a, value_b);
        assert_that(expected, is_equal(value_a));
    });

    describe_test("testing same number length (special: 0 x 0)", []() {
        math::digits_type value_a = {0};        // 0
        const math::digits_type value_b = {0};  // 0
        const math::digits_type expected = {0}; // 0

        math::big_integer_multiplication bimult;
        bimult.calculate(value_a, value_b);
        assert_that(expected, is_equal(value_a));
    });

    describe_test("testing different number length (a < b)", []() {
        math::digits_type value_a = {4, 3, 2, 1};                    // 1234
        const math::digits_type value_b = {9, 8, 7, 6, 5};           // 56789
        const math::digits_type expected = {6, 2, 6, 7, 7, 0, 0, 7}; // 70077626

        math::big_integer_multiplication bimult;
        bimult.calculate(value_a, value_b);
        assert_that(expected, is_equal(value_a));
    });

    describe_test("testing different number length (a > b)", []() {
        math::digits_type value_a = {9, 8, 7, 6, 5};                 // 56789
        const math::digits_type value_b = {4, 3, 2, 1};              // 1234
        const math::digits_type expected = {6, 2, 6, 7, 7, 0, 0, 7}; // 70077626

        math::big_integer_multiplication bimult;
        bimult.calculate(value_a, value_b);
        assert_that(expected, is_equal(value_a));
    });
});

