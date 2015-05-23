///
/// @author  Thomas Lehmann
/// @file    test_big_integer_sum.cxx
/// @brief   testing of @ref math::big_integer_sum
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
#include <math/big_integer_sum.h>

using namespace unittest;
using namespace matcher;

/// testing of class @ref math::big_integer_sum
describe_suite("testing math::big_integer_sum", [](){
    describe_test("testing same number length (length remains)", []() {
        math::digits_type value_a = {4, 2, 0, 1};        // 1024
        const math::digits_type value_b = {8, 4, 0, 2};  // 2048
        const math::digits_type expected = {2, 7, 0, 3}; // 3072

        math::big_integer_sum bisum;
        bisum.calculate(value_a, value_b);
        assert_that(expected, is_equal(value_a));
    });

    describe_test("testing same number length (length does change)", []() {
        math::digits_type value_a = {9, 9, 9, 9};        // 9999
        const math::digits_type value_b = {9, 9, 9, 9};  // 9999
        const math::digits_type expected = {8, 9, 9, 9, 1}; // 19998

        math::big_integer_sum bisum;
        bisum.calculate(value_a, value_b);
        assert_that(expected, is_equal(value_a));
    });

    describe_test("testing different number length (a < b)", []() {
        math::digits_type value_a = {1};              // 1
        const math::digits_type value_b = {3, 2, 1};  // 123
        const math::digits_type expected = {4, 2, 1}; // 124

        math::big_integer_sum bisum;
        bisum.calculate(value_a, value_b);
        assert_that(expected, is_equal(value_a));
    });

    describe_test("testing different number length (a > b)", []() {
        math::digits_type value_a = {3, 2, 1};        // 123
        const math::digits_type value_b = {1};        // 1
        const math::digits_type expected = {4, 2, 1}; // 124

        math::big_integer_sum bisum;
        bisum.calculate(value_a, value_b);
        assert_that(expected, is_equal(value_a));
    });

    describe_test("testing different number length (a has no digit)", []() {
        math::digits_type value_a = {};               // no digit
        const math::digits_type value_b = {3, 2, 1};  // 123
        const math::digits_type expected = {3, 2, 1}; // 123

        math::big_integer_sum bisum;
        bisum.calculate(value_a, value_b);
        assert_that(expected, is_equal(value_a));
    });

    describe_test("testing different number length (b has no digit)", []() {
        math::digits_type value_a = {3, 2, 1};        // 123
        const math::digits_type value_b = {};         // no digit
        const math::digits_type expected = {3, 2, 1}; // 123

        math::big_integer_sum bisum;
        bisum.calculate(value_a, value_b);
        assert_that(expected, is_equal(value_a));
    });

    describe_test("testing power of 2 via addition", []() {
        math::digits_type value_a = {1};
        math::big_integer_sum bisum;
        for (auto n = 0; n < 300; ++n) {
            const auto value_b = value_a;
            bisum.calculate(value_a, value_b);
        }

        std::string given = "";
        for (const auto& digit: value_a) {
            given = std::to_string(static_cast<uint32_t>(digit)) + given;
        }

        const std::string expected
            = "2037035976334486086268445688409378161051468393665936250636140449354381299763336706183397376";
        assert_that(expected, is_equal(given));
    });
});

