///
/// @author  Thomas Lehmann
/// @file    test_fraction.cxx
/// @brief   testing of @ref math::fraction
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
#include <math/fraction.h>
#include <cstdint>

using namespace unittest;
using namespace matcher;

/// testing of class @ref math::fraction
describe_suite("testing math::fraction", [](){
    describe_test("testing default", []() {
        constexpr math::fraction<int32_t> f(1, 2);
        assert_that(1, is_equal(f.get_numerator()));
        assert_that(2, is_equal(f.get_denominator()));
    });

    describe_test("testing sum of two fractions", []() {
        constexpr math::fraction<int32_t> f1(1, 2);
        constexpr math::fraction<int32_t> f2(1, 3);
        constexpr math::fraction<int32_t> f3 = f1 + f2;
        assert_that(5, is_equal(f3.get_numerator()));
        assert_that(6, is_equal(f3.get_denominator()));
    });

    describe_test("testing difference of two fractions", []() {
        constexpr math::fraction<int32_t> f1(1, 2);
        constexpr math::fraction<int32_t> f2(1, 3);
        constexpr math::fraction<int32_t> f3 = f1 - f2;
        assert_that(1, is_equal(f3.get_numerator()));
        assert_that(6, is_equal(f3.get_denominator()));
    });

    describe_test("testing product of two fractions", []() {
        constexpr math::fraction<int32_t> f1(2, 3);
        constexpr math::fraction<int32_t> f2(3, 5);
        constexpr math::fraction<int32_t> f3 = f1 * f2;
        assert_that(6, is_equal(f3.get_numerator()));
        assert_that(15, is_equal(f3.get_denominator()));
    });

    describe_test("testing product of two fractions", []() {
        constexpr math::fraction<int32_t> f1(2, 3);
        constexpr math::fraction<int32_t> f2(3, 5);
        constexpr math::fraction<int32_t> f3 = f1 / f2;
        assert_that(10, is_equal(f3.get_numerator()));
        assert_that(9, is_equal(f3.get_denominator()));
    });

    describe_test("testing comparison of two fractions to be equal", []() {
        constexpr math::fraction<int32_t> f1(1, 2); // 0.5
        constexpr math::fraction<int32_t> f2(1, 2); // 0.5
        constexpr math::fraction<int32_t> f3(3, 4); // 0.75
        constexpr math::fraction<int32_t> f4(3, 6); // same as f1: 0.5
        assert_that(f1, is_equal(f2));
        assert_that(f1, is_not(is_equal(f3)));
        assert_that(f1, is_equal(f4));
        assert_that(f4, is_equal(f1));
    });

    describe_test("testing stream", []() {
        constexpr math::fraction<int32_t> f(1, 2);
        std::stringstream stream;
        stream << f;
        assert_that(std::string("fraction(1, 2)"), is_equal(stream.str()));
    });
});
